/**
 * @file       <file>.c
 * @headerfile <hdrfile>.h
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

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief kickoff channel sampling
 * @param none
 * @retval none
 */
void
  ana_start( void )
{
  EQADC.CFCR[5].B.MODE = 5;   /**< switchover to ss rising edge trig'd */

  /* edma ch11 is driven by rfifo5: */
  EDMA.TCD[11].SADDR  = 0xFFF80046;             /**< rfifo5 pop reg */
  EDMA.TCD[11].SMOD   = 0;
  EDMA.TCD[11].SSIZE  = 1;                      /**< 1 == sizeof(uint16_t) */
  EDMA.TCD[11].DMOD   = 0;
  EDMA.TCD[11].DSIZE  = 1;                      /**< 1 == sizeof(uint16_t) */
  EDMA.TCD[11].SOFF   = 0;                      /**< pop reg is constant! */
  EDMA.TCD[11].SLAST  = 0;                      /*               ^^       */
  EDMA.TCD[11].NBYTES = sizeof(uint16_t);       /**< minor size */
  EDMA.TCD[11].DADDR  = (vuint32_t)samples;
  EDMA.TCD[11].CITERE_LINK = 0;                 /**< no linking */
  EDMA.TCD[11].CITER = AS_SIZE;
  EDMA.TCD[11].DOFF = sizeof(uint16_t);         /**< += */
  EDMA.TCD[11].DLAST_SGA = AS_SIZE * -sizeof(uint16_t);
  EDMA.TCD[11].BITERE_LINK = 0;                 /**< no linking */
  EDMA.TCD[11].BITER = AS_SIZE;                 /**< major cycles */
  EDMA.TCD[11].BWC = 2;                         /**< 4 cyc stall */
  EDMA.TCD[11].MAJORE_LINK = 0;                 /**< no linking */
  EDMA.TCD[11].E_SG = 0;                        /**< no scatter/gather */
  EDMA.TCD[11].D_REQ = 0;                       /**< self arm for next trig */
  EDMA.TCD[10].INT_MAJ = 1;                     /**< irq when major complete! */
  EDMA.SERQR.R = 11;                            /**< unmask self - ready to go */
  INTC.PSR[22].B.PRI = 6;                       /**< unmask ch11 handler */
  EQADC.IDCR[5].B.RFDS = 1;                     /**< select dma */
  EQADC.IDCR[5].B.RFDE = 1;                     /**< rfifo drain enable */

  /* edma ch10 is driven by cfifo5: */
  EDMA.TCD[10].SADDR  = (vuint32_t)&cmd_queue[0];
  EDMA.TCD[10].SMOD   = 0;
  EDMA.TCD[10].SSIZE  = 2;                      /**< 2 == sizeof(uint32_t) */
  EDMA.TCD[10].DMOD   = 0;
  EDMA.TCD[10].DSIZE  = 2;                      /**< 2 == sizeof(uint32_t) */
  EDMA.TCD[10].SOFF   = sizeof(uint32_t);       /**< += */
  EDMA.TCD[10].NBYTES = sizeof(uint32_t);       /**< minor size */
  EDMA.TCD[10].SLAST  = AS_SIZE * -sizeof(uint32_t);
  EDMA.TCD[10].DADDR  = (vuint32_t)&EQADC.CFPR[5].R;
  EDMA.TCD[10].CITERE_LINK = 0;                 /**< no linking */
  EDMA.TCD[10].CITER = AS_SIZE;
  EDMA.TCD[10].DOFF = 0;                        /**< push reg is constant! */
  EDMA.TCD[10].DLAST_SGA = 0;                   /*                ^^       */
  EDMA.TCD[10].BITERE_LINK = 0;                 /**< no linking */
  EDMA.TCD[10].BITER = AS_SIZE;                 /**< major cycles */
  EDMA.TCD[10].BWC = 2;                         /**< 4 cyc stall */
  EDMA.TCD[10].MAJORE_LINK = 0;                 /**< no linking */
  EDMA.TCD[10].E_SG = 0;                        /**< no scatter/gather */
  EDMA.TCD[10].D_REQ = 0;                       /**< self arm for next trig */
  EDMA.TCD[10].INT_MAJ = 0;
  EDMA.SERQR.R = 10;                            /**< unmask self - ready to go */
  EQADC.IDCR[5].B.CFFS = 1;                     /**< select dma */
  EQADC.IDCR[5].B.CFFE = 1;                     /**< cfifo fill enable */

  EQADC.CFCR[5].B.SSE = 1;    /**< gate etrig through */
  PIT.RTI.TCTRL.B.TEN = 1;    /**< start rti - etrig source */
}
/* --| INTERNAL |--------------------------------------------------------- */