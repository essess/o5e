/**
 * @file       task_ana.c
 * @headerfile task_ana.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/ana/task_ana_prv.h"
#include "cocoos.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create and initialize the analog processing task
 * @retval none
 */
void
  task_ana_create( calblk_t volatile *pblk )
{
  /* pblk previously validated */
  void (*const ptask)(void) = pblk->test.enable ? task_ana_test : task_ana;
  if( task_create( ptask, TASKPRI_ANA, 0, 0, 0 ) == NO_TID )
    err_push( CODE_TANA_CREATETID );
}

/* --| INTERNAL |--------------------------------------------------------- */
