/**
 * @file       process_w.c
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
 * @brief write
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_w( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PWPTR );
  err_assert( *pbuff == 'w', CODE_TUNER_PWCMD );

  #pragma push
  #pragma pack(1)
  typedef struct
  {
    uint8_t  cmd;     /**< 'w' */
    uint16_t page;
    uint16_t page_offset;
    uint16_t len;
    /* data starts here */
  } cmd_t;
  #pragma pop
  err_assert( len >= sizeof(cmd_t), CODE_TUNER_PWLEN );

  cmd_t *const c = (cmd_t*)pbuff;
  unsigned const blk_offset = (c->page*PAGE_BYTESIZE)+c->page_offset;
  uint8_t *const pdst = getcalblk_ptr_byoffset( blk_offset, c->len );
  if( pdst )
  {
    uint8_t const *const psrc = &pbuff[sizeof(cmd_t)];
    bytecpy( pdst, psrc, c->len );
    *pbuff = OK;
  }
  else
  {
    err_push( CODE_TUNER_PWRANGE );
    *pbuff = OUT_OF_RANGE;
  }

  return sizeof(uint8_t);
}