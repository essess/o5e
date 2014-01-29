/**
 * @file       edma_reghnd.c
 * @headerfile core_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "platform/core/mpc5634m/edma/edma_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @brief register an individual dma error callback
 */
void
  edma_reg_errhnd( unsigned channel,
                   edma_err_cb_t cb )
{
  if( channel && (channel <= 31) && cb )
  {
    edma_err_cb[channel] = cb;
    EDMA.SEEIR.R = (uint8_t)channel;  /**< enable channel error */
  }
}