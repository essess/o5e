/**
 * @file       flash_get.c
 * @headerfile flash.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/flash/flash_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

flash_t f =
{
  .state = FLSTATE_IDLE,
  .blkptr = BLK4
};

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief initialize flash (on first call) and returns the current context
 * @param none
 * @retval flash_t* reference to flash context
 */
flash_t *
  flash_get( void )
{
  static flash_t *fptr = 0;
  if( !fptr )
  {
    CFLASH0.LMLR.R  = LMLR_PW;   /**< unlock lock regs and verify */
    CFLASH0.SLMLR.R = SLMLR_PW;
    if( CFLASH0.LMLR.B.LME && CFLASH0.SLMLR.B.SLE )
      fptr = &f;
  }
  return fptr;
}

/* --| INTERNAL |--------------------------------------------------------- */
