/**
 * @file       process_Q.c
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
#include "util.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief query
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_Q( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PQPTR );
  err_assert( *pbuff == 'Q', CODE_TUNER_PQCMD );
  err_assert( len == 1, CODE_TUNER_PQLEN );

  /* queryCommand = "Q"  ; Verify against signature. 20 bytes */
  uint8_t const sig[] = { 'M','S','h','i','f','t',' ','2','.','1','1','1' };
  *pbuff++ = OK;
  len = sizeof( sig );
  bytecpy( pbuff, sig, len );
  return len + sizeof(uint8_t);     /**< += sizeof(OK) */
}