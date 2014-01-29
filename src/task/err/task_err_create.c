/**
 * @file       task_err_create.c
 * @headerfile task_err.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "task/task_err.h"
#include "task/err/task_err_prv.h"
#include "trap.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create and initialize the error display task
 * @retval none
 */
void
  task_err_create( void )
{
  uint8_t const task_err_tid = task_create( &task_err, TASKPRI_ERR, 0, 0, 0 );
  trap( task_err_tid != NO_TID );
}

/* --| INTERNAL |--------------------------------------------------------- */
