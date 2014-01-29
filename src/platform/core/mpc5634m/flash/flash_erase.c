/**
 * @file       flash_erase.c
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
 * @brief start an erase operation on current block
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 * @note use @see { flash_busy_chk } to poll for when cycle is complete
 */
flash_err_t
  flash_erase( flash_t *fptr )
{
  flash_err_t e = FLERR_UNKNOWN;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_READY) )
  {
    CFLASH0.LMSR.R |= BLKBM_BYADDR(fptr->blkptr);
    *(int*)FLASH_START = 0;   /**< erase interlock write */
    CFLASH0.MCR.B.EHV = 1;    /**< start                 */
    fptr->state = FLSTATE_BUSY;
    e = FLERR_OK;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
