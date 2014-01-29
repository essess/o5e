/**
 * @file       main.c
 * @headerfile main.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "err.h"
#include "cal.h"
#include "etpu.h"
#include "ana.h"
#include "global.h"
#include "calblk.h"
#include "task/task_tuner.h"
#include "task/task_err.h"
#include "task/task_engpos.h"
#include "task/task_ana.h"
#include "task/task_toothgen.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

volatile global_t global;

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @public
 * @note on entry, the following is assumed and performed by platform
 *       initialization
 *      - ALL interrupts to core and anything external is unmasked
 *      - ALL interrupts have a default hander assigned
 *      - the system timebase is initialized to run at 1KHz, your tick hander
 *        needs to be registered still
 *      - the timebases have NOT been started yet, use core_start_timers() to do that
 *      - any hardware which is fixed and not configured by cal options is
 *        setup to its default SAFE state.
 */
void
  main(void)
{
  os_init();
  err_init( 0 );
  etpu_init();
  if( cal_init() )
  {
    /* all tasks dependent on proper cal present, create here: */
    calblk_t volatile *pblk = (calblk_t*)cal_getblk_ptr();
    if( pblk && (sizeof(calblk_t)<=cal_getblk_bytesize()) )
    {
      if( pblk->test.enable )
      {
        err_push( CODE_MISC_TESTMODE );
        task_toothgen_create( pblk );
      }
      /* these tasks run regardless of test mode: */
      task_ana_create( pblk );
      task_engpos_create();
    }
    else
      err_push( CODE_MISC_CALBLK );
  }
  else
    err_push( CODE_MISC_NOCAL );
  task_err_create();
  task_tuner_create();
  core_tick_reg( &os_tick );
  core_start_timers();
  os_start();
}