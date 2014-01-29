/**
 * @file       flash_swap.c
 * @headerfile flash.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/flash/flash_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief swap to other flash storage block
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 * @note use @see{ flash_getblkptr } to get a raw ref to the new block
 */
flash_err_t
  flash_swap( flash_t *fptr )
{
  flash_err_t e = FLERR_BUSY;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_IDLE) )
  { /* if blkptr cannot be determined, at least default to BLK4 */
    fptr->blkptr = (fptr->blkptr==BLK4) ? BLK5 : BLK4;
    e = FLERR_OK;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
