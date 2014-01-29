/**
 * @file       flash_getblk_bytesize.c
 * @headerfile flash.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
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
 * @brief get bytesize of current flash block
 * @param[in] fptr flash context
 * @retval unsigned size of flash block in bytes
 */
unsigned
  flash_getblk_bytesize( flash_t *fptr )
{
  return (fptr ==  &f) ? BLKSIZE : 0;
}

/* --| INTERNAL |--------------------------------------------------------- */