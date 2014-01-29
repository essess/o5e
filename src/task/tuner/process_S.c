/**
 * @file       process_S.c
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
 * @brief signature
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_S( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PSPTR );
  err_assert( *pbuff == 'S', CODE_TUNER_PSCMD );
  err_assert( len == 1, CODE_TUNER_PSLEN );

  /* versionInfo = "S"  ; Put this in the title bar. */
  uint8_t const ver[] = { 'o','5','e',' ','0','.','5','.','0' };
  *pbuff++ = OK;
  len = sizeof( ver );
  bytecpy( pbuff, ver, len );
  return len + sizeof(uint8_t);     /**< += sizeof(OK) */
}