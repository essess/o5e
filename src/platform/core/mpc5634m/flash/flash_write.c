/**
 * @file       flash_write.c
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
 * @brief do doubleword write to designated offset of current block
 * @param[in] fptr flash context
 * @param[in] o offset into the current block, must be on modulo 8
 *              boundaries or FLERR_ALIGNMENT results
 * @param[in] dw reference to doubleword data
 * @retval flash_err_t FLERR_OK on success
 * @note use @see { flash_busy_chk } to poll for when cycle is complete
 */
flash_err_t
  flash_write( flash_t *fptr,
               uint32_t o,
               uint64_t *dw )
{
  flash_err_t e = FLERR_UNKNOWN;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_READY) )
  {
    if( o%sizeof(uint64_t) )
      return FLERR_ALIGNMENT;

    fptr->state = FLSTATE_BUSY;
    uint64_t *const dst = (uint64_t*)((uint32_t)fptr->blkptr + o);
    *dst = *dw;
    CFLASH0.MCR.B.EHV = 1;
    e = FLERR_OK;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
