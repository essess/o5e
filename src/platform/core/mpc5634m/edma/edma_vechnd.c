/**
 * @file       edma_vechnd.c
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

edma_err_cb_t edma_err_cb[32];

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

void
  vector10( void )
{
  uint32_t const esr = EDMA.ESR.R;
  for( unsigned i=0; i <= 31 ;i++ )
  {
    if( EDMA.ERL.R & (1u<<i) )
    {
      if( edma_err_cb[i] )
        edma_err_cb[i](esr);
      EDMA.CER.R = (uint8_t)i;
    }
  }
}
