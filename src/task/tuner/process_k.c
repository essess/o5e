/**
 * @file       process_k.c
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
 * @brief crc a block
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_k( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PKPTR );
  err_assert( *pbuff == 'k', CODE_TUNER_PKCMD );

  #pragma push
  #pragma pack(1)
  typedef struct
  {
    uint8_t  cmd;     /**< 'k' */
    uint16_t page;
    uint16_t page_offset;
    uint16_t len;
  } cmd_t;
  err_assert( len == sizeof(cmd_t), CODE_TUNER_PKLEN );

  typedef struct
  {
    uint8_t  status;
    uint32_t crc;
  } reply_t;
  #pragma pop

  cmd_t *const c = (cmd_t*)pbuff;
  unsigned const blk_offset = (c->page*PAGE_BYTESIZE)+c->page_offset;
  uint8_t *const pblk = getcalblk_ptr_byoffset( blk_offset, c->len );
  if( pblk )
  {
    reply_t *const r = (reply_t*)pbuff;
    r->crc = crc32( 0, pblk, c->len );
    r->status = OK;
    len = sizeof(reply_t);
  }
  else
  {
    err_push( CODE_TUNER_PKRANGE );
    *pbuff = OUT_OF_RANGE;
    len = sizeof(uint8_t);
  }
  return len;
}