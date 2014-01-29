/**
 * @file       err_destroy.c
 * @headerfile err.h
 * @author     sstasiak
 * @note       do not use traps in this api
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "trap.h"
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
 * @brief return err_t back to the free pool
 * @param[in] e previously pop'd err
 * @retval none
 * @note { threadsafe }
 */
void
  err_destroy( err_t const *e )
{
  trap( e );
  core_declare_state(s);
  core_disable_interrupts(s);
  err_free_root = lifo_push( err_free_root, (void*)e );
  core_restore_state(s);
}
