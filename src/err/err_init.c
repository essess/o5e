/**
 * @file       err_init.c
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
#include "err.h"
#include "err/err_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
err_t err_pool[ERR_DEPTH];
err_t *err_free_root = 0;
fifo_t err_fifo_root;
err_cb_t *notify = 0;
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief init code logger
 * @param[in] fptr function called upon first code pushed into an empty stack
 * @retval none
 * @note { not threadsafe }
 */
void
  err_init( err_cb_t *fptr )
{
  trap( ERR_DEPTH );
  fifo_init( &err_fifo_root );
  for(register i=0; i < ERR_DEPTH ;i++)   /**< loadup free pool          */
    err_free_root = lifo_push( err_free_root, &err_pool[i] );
  notify = fptr;                          /**< null is ok                */
}
