/**
 * @file       process_p.c
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
 * @brief pop an error code off the stack
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_p( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PPPTR );
  err_assert( *pbuff == 'p', CODE_TUNER_PPCMD );
  err_assert( len == 1, CODE_TUNER_PPLEN );

  err_t const * const pe = err_pop();
  uint32_t code = 0;
  if( pe )
  {
    code = err_get_code( pe );
    err_destroy( pe );
  }
  /* breakdown for easier reporting */
  *pbuff++ = (uint8_t)GET_MODULE( code );
  *pbuff   = (uint8_t)GET_CODE( code );
  return sizeof(uint16_t);
}
