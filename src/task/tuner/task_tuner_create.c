/**
 * @file       task_tuner_create.c
 * @headerfile task_tuner.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/tuner/task_tuner_prv.h"
#include "cocoos.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create the tuner i/o task
 * @retval none
 */
void
  task_tuner_create( void )
{
  uint8_t const tid = task_create( &task_tuner, TASKPRI_TUNER, 0, 0, 0 );
  err_assert( tid != NO_TID, CODE_TUNER_TCTID );
}

/* --| INTERNAL |--------------------------------------------------------- */
