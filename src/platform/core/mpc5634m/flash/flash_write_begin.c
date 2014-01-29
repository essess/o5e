/**
 * @file       flash_write_begin.c
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
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief unlock the current block and prepare for a series of write
 *        operations
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_write_begin( flash_t *fptr )
{
  flash_err_t e = FLERR_BUSY;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_IDLE) )
  {
    fptr->state = FLSTATE_READY;
    uint32_t const mask = ~BLKBM_BYADDR(fptr->blkptr);
    CFLASH0.LMLR.R  &= mask; /**< clr to unlock current block */
    CFLASH0.SLMLR.R &= mask;
    CFLASH0.MCR.B.PGM = 1;
    e = FLERR_OK;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
