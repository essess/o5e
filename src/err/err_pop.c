/**
 * @file       err_pop.c
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
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief pop oldest error from the stack
 * @param none
 * @retval err_t* err or 0 if none
 * @note { threadsafe }
 */
err_t const *
  err_pop( void )
{
  core_declare_state(s);
  core_disable_interrupts(s);
  err_t const * const e = fifo_pop( &err_fifo_root );
  core_restore_state(s);
  if( !e && notify )
    notify( CODE_NONE );  /**< stack empty */
  return e;
}
