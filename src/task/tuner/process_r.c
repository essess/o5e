/**
 * @file       process_r.c
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
 * @brief read
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_r( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PRPTR );
  err_assert( *pbuff == 'r', CODE_TUNER_PRCMD );

  #pragma push
  #pragma pack(1)
  typedef struct
  {
    uint8_t  cmd;     /**< 'r' */
    uint16_t page;
    uint16_t page_offset;
    uint16_t len;
  } cmd_t;
  #pragma pop
  err_assert( len == sizeof(cmd_t), CODE_TUNER_PRLEN );

  cmd_t *const c = (cmd_t*)pbuff;
  unsigned const blk_offset = (c->page*PAGE_BYTESIZE)+c->page_offset;
  uint8_t *const psrc = getcalblk_ptr_byoffset( blk_offset, c->len );
  if( psrc )
  {
    *pbuff++ = OK;
    len = c->len;
    bytecpy( pbuff, psrc, len );
    len += sizeof(uint8_t); /**< += sizeof(OK) */
  }
  else
  {
    err_push( CODE_TUNER_PRRANGE );
    *pbuff = OUT_OF_RANGE;
    len = sizeof(uint8_t); /**< = sizeof(OK) */
  }
  return len;
}