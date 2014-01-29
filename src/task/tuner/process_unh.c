/**
 * @file       process_unh.c
 * @headerfile task_tuner_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/tuner/task_tuner_prv.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief unhandled, but correctly formed '001' cmd, rolled in from the tuner
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_unh( uint8_t *pbuff,
               uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PUPTR );
  err_assert( len, CODE_TUNER_PULEN );

  *pbuff = UNHANDLED_CMD;
  return sizeof(uint8_t);
}