/**
 * @file       task_tuner_prv.c
 * @headerfile task_tuner_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/tuner/task_tuner_prv.h"
#include "cal.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief get a bounds checked block reference into the calibration space
 * @param[in] offset byte offset into calibration
 * @param[in] bytesize expected byte size of access to be performed upon the
 *                     return reference (internal limit checking performed)
 * @retval uint8_t* absolute reference, null if bound check fails
 */
uint8_t *
  getcalblk_ptr_byoffset( unsigned offset,
                          unsigned bytesize )
{
  uint8_t *const pblk = cal_getblk_ptr();
  if( pblk && ((offset+bytesize) <= cal_getblk_bytesize()) )
    return &pblk[offset];
  err_push( CODE_TUNER_TTPGCBPBO );
  return 0;
}
