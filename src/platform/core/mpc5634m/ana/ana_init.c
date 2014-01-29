/**
 * @file       ana_init.c
 * @headerfile ana.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "err.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "platform/core/mpc5634m/ana/ana_prv.h"
#include "platform/core/mpc5634m/core_prv.h"

/* --| TYPES    |--------------------------------------------------------- */

/* write/read configuration command helpers: */
#define ADC_REG_ADDRESS(x_) ((x_&0xffu)<<0)
#define ADC_REG_VALUE(x_)   ((x_&0xffffu)<<8)
#define ADC_REG_WRITE       (0u)
#define ADC_REG_READ        (1u<<24)

/* control register (0x01) helpers: */
#define ADCx_CR             (0x01)
#define ADCx_EN             (1u<<15)
#define ADCx_DIS            (0u<<15)
#define ADCx_CLK_PS(x_)     ((x_&0x1fu)<<0)

#define ADC1_WRITE_CONFIG(x_)   \
          (ADC_REG_ADDRESS(ADCx_CR)|ADC_REG_VALUE(x_)|ADC_REG_WRITE|BN(1))
#define SYSCLK_DIV8 (3) /**< ADCx_CR prescalar value */

/* --| STATICS  |--------------------------------------------------------- */

ana_t ana;
vuint16_t samples[AS_SIZE]; /**< updated directly from dma */

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief initialize analog subsystem
 * @param[in] rate desired sample rate in Hz (50->1000Hz inclusive)
 * @param[in] pf conversion done callback, callers signal that samples
 *               have been updated
 * @retval uint16_t* reference to sample array indexed by @see { ana_src_t }
 *                   or null on failure
 * @note all channels are updated at the same rate
 */
vuint16_t const *
  ana_init( uint32_t rate,
            ana_evt_cb_t *pf )
{
  // NOTE - hopefully caller has waitd 8ms+ before calling us (REFBYPC stabilization time)
  static vuint16_t const *psamples = 0;
  if( !psamples )
  {
    if( pf )
    {
      ana.pcb = pf;
      if( (rate >= 50) && (rate <= 1000) )
      {
        /* we're using adc1, cfifo5, rfifo5, dma, rti as etrig */
        PIT.RTI.TCTRL.B.TEN = 0;
        PIT.RTI.LDVAL.R = ((XTAL_HZ/rate)-1); /**< RTI clk source is xtal */

        SIU.ETISR.B.TSEL5 = 0;    /**< use SIU_ISEL3[ETSEL5] ... */
        SIU.ISEL3.B.ETSEL5 = 1;   /**< ... RTI as trig source */
        EQADC.CFCR[5].B.MODE = 1; /**< sw trigger single scan */
        EQADC.CFPR[5].R =         /**< loadup desired adc1 config */
          ADC1_WRITE_CONFIG(ADCx_EN|ADCx_CLK_PS(SYSCLK_DIV8)) | EOQ;
        if( !EQADC.FISR[5].B.EOQF )
        {
          EQADC.CFCR[5].B.SSE = 1;  /**< clock through config */
          while( !EQADC.FISR[5].B.EOQF ) {}
          EQADC.FISR[5].B.EOQF = 1; /**< clr */
        }
        EQADC.CFCR[5].B.MODE = 0; /**< disable, _start() will select new mode */
        edma_reg_errhnd( 10, &ana_errhnd );   /**< catch cfifo5 dma errors */
        edma_reg_errhnd( 11, &ana_errhnd );   /**< catch rfifo5 dma errors */
        psamples = samples;
      }
      else
        err_push( CODE_ANA_INITRATE );
    }
    else
      err_push( CODE_ANA_INITPF );
  }
  else
    err_push( CODE_ANA_REINIT );
  return psamples;
}
/* --| INTERNAL |--------------------------------------------------------- */