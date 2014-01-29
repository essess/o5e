/**
 * @file       ana_vechnd.c
 * @headerfile ana_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "platform/core/mpc5634m/ana/ana_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @brief handle rfifo5 dma done and bubble back to caller
 */
void
  vector22( void )
{
  ana.pcb( AE_READY );
  EDMA.CIRQR.R = 11;    /**< clr int req reg */
}