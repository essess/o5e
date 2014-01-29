/**
 * @file       core_start_timers.c
 * @headerfile core.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "core.h"
#include "platform/core/mpc5634m/mpc5634m.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief start ALL timebases
 * @param none
 * @retval none
 */
void
  core_start_timers( void )
{
  register int r;
  asm                       /**< enable core timebase */
  {
    mfhid0  r
    ori     r, r, 0x4000
    mthid0  r
  }
  EMIOS.MCR.B.GTBE = 1;     /**< enable emios and tpu timebases */
}

/* --| INTERNAL |--------------------------------------------------------- */
