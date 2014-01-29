/**
 * @file       etpu_init.c
 * @headerfile etpu.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "etpu.h"
#include "err.h"
#include "platform/core/mpc5634m/etpu/mpc563m_vars.h"
#include "platform/core/mpc5634m/etpu/etpu_set.h"
#include "etpu/etpu_util.h"
#include "platform/core/mpc5634m/mpc5634m.h"

#define ETPU_TCR1_FREQ  (10000000)  /**< see prescalar note below */

/* --| TYPES    |--------------------------------------------------------- */

typedef union
{
  uint16_t reg;
  struct
  {
    uint16_t    :3;       /*  */
    uint16_t  pa:3;       /*  */
    uint16_t obe:1;       /*  */
    uint16_t ibe:1;       /*  */
    uint16_t dsc:2;       /*  */
    uint16_t ode:1;       /*  */
    uint16_t hys:1;       /*  */
    uint16_t src:2;       /*  */
    uint16_t wpe:1;       /*  */
    uint16_t wps:1;       /*  */
  };
} pcr_t;

/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief initialize etpu, start timebase with @see { core_start_timers }
 * @param none
 * @retval void
 */
void
  etpu_init( void )
{
  struct etpu_config_t const etpu_config =
  {
    .mcr     = FS_ETPU_VIS_OFF |
               FS_ETPU_GLOBAL_TIMEBASE_DISABLE |
               FS_ETPU_MISC_ENABLE,
    .misc    = FS_ETPU_MISC,
    .ecr_a   = FS_ETPU_ENTRY_TABLE |
               FS_ETPU_CHAN_FILTER_3SAMPLE |
               FS_ETPU_ENGINE_ENABLE |
               FS_ETPU_FILTER_CLOCK_DIV8,
    .tbcr_a  = FS_ETPU_ANGLE_MODE_ENABLE |
               FS_ETPU_TCR2CTL_RISE |
               FS_ETPU_TCRCLK_INPUT_DIV2CLOCK |
               FS_ETPU_TCRCLK_MODE_2SAMPLE |
               FS_ETPU_TCR1CTL_DIV2 |
               FS_ETPU_TCR1_PRESCALER(4),     /**< tcr1 f=80MHz/2/4=10MHz  */
    .stacr_a = FS_ETPU_TCR1_STAC_SERVER |     /**< aka REDCR ->angle mode  */
               FS_ETPU_TCR1_STAC_ENABLE |     /*   requires tpu to be stac */
               FS_ETPU_TCR2_STAC_SERVER |     /*   server                  */
               FS_ETPU_TCR2_STAC_ENABLE,
    .wdtr_a  = FS_ETPU_WDM_DISABLED,
    .ecr_b   = 0, /**< unused */
    .tbcr_b  = 0, /**< unused */
    .stacr_b = 0, /**< unused */
    .wdtr_b  = 0  /**< unused */
  };

  if( fs_etpu_init( etpu_config,
                    (uint32_t*)etpu_code,
                    sizeof(etpu_code),
                    (uint32_t*)etpu_globals,
                    sizeof(etpu_globals) ) == FS_ETPU_ERROR_NONE )
  {
    if( fs_etpu2_init( etpu_config,
                       0 ) != FS_ETPU_ERROR_NONE )
      err_push( CODE_ETPU_INIT2 );
  }
  else
    err_push( CODE_ETPU_INIT );

  /* setup default pins used by tpu: */
  /* 31 = toothgen crank out */
  /* 30 = toothgen cam out   */
  /* 1 = cam in   */
  /* 0 = crank in */

  pcr_t const tg_pcr =
  {
    .pa = 3,  .obe = 1,  .ibe = 1,  .dsc = 0,  .ode = 0,
    .hys = 0, .src = 3,  .wpe = 1,  .wps = 0
  };
  SIU.PCR[144].R = tg_pcr.reg;
  SIU.PCR[145].R = tg_pcr.reg;

}

/**
 * @public
 * @brief returns tcr1 timebase freq
 */
unsigned
  etpu_tcr1_freq( void )
{
  return ETPU_TCR1_FREQ;
}

/* --| INTERNAL |--------------------------------------------------------- */
