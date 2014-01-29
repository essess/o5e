/**
 * @file       flash_getblkptr.c
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
 * @brief get raw reference to current flash block
 * @attention DO NOT deref while performing other operations upon flash
 * @param[in] fptr flash context
 * @retval uint8_t const* raw reference to the current flash block, 0 otherwise
 * @note assume size is CAL_SIZE
 */
uint8_t const*
  flash_getblk_ptr( flash_t *fptr )
{
  uint8_t const* blkptr = 0;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_IDLE) )
    blkptr = fptr->blkptr;
  return blkptr;
}

/* --| INTERNAL |--------------------------------------------------------- */
