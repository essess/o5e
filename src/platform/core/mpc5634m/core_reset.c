/**
 * @file       core_reset.c
 * @headerfile core.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/mpc5634m.h"
#include "core.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief hard reset the core while asserting the external line also
 * @param none
 * @retval none
 */
void
  core_reset( void ) __attribute__((noreturn))
{
  while(1)
  {
      SIU.SRCR.B.SSR = 1;
      asm { msync };
  }
}

/* --| INTERNAL |--------------------------------------------------------- */
