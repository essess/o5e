/**
 * @file       err_push.c
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
#include "trap.h"
#include "err.h"
#include "err/err_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief push an error code into the stack
 * @param[in] code error code
 * @retval none
 * @note { threadsafe }
 */
void
  err_push( uint32_t code )
{
  trap( code != CODE_NONE );   /*< why are you not pushing a code? */
  core_declare_state(s);

  /* the lifo/fifo api is not threadsafe, and I want any context to feel free
   * to call this api. wrapping in a critical section ensures threadsafety.
   */

  core_disable_interrupts(s);
  err_t *const e = lifo_pop( &err_free_root );
  core_restore_state(s);

  if( e )
  {
    e->ts = core_get_timebase();
    e->code = code;

    core_disable_interrupts(s);
    fifo_push( &err_fifo_root, e );
    core_restore_state(s);

    if( notify )
      notify( code );
  }
  else
  {
    /* no more blocks - signalling an error won't help much either */
  }
}
