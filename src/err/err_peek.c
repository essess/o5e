/**
 * @file       err_peek.c
 * @headerfile err.h
 * @author     sstasiak
 * @note       do not use traps in this api
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "core.h"
#include "err.h"
#include "err/err_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

static int
  first_item( void *i, void *d )
{
  /* if this is called, there are codes in the stack */
  /* the first time we're called, is with the first  */
  /* item -> fifo_map returns this item (i)          */
  (void)i;
  (void)d;
  return ~0;
}
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief nondestructively return the topmost error if present
 * @param none
 * @retval uint32_t err code or CODE_NONE
 * @note { threadsafe (but expensive) }
 */
uint32_t
  err_peek( void )
{
  uint32_t code = CODE_NONE;
  core_declare_state(s);
  core_disable_interrupts(s);
  err_t const * const e = fifo_map( &err_fifo_root,
                                    &first_item,
                                    0 );
  if( e )
    code = err_get_code( e );
  core_restore_state(s);
  return code;
}