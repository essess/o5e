/**
 * @file       task_toothgen_create.c
 * @headerfile task_toothgen.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "task/task_toothgen.h"
#include "task/toothgen/task_toothgen_prv.h"
#include "err.h"
#include "etpu.h"
#include "etpu/etpu_toothgen.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create the toothgen control task
 */
void
  task_toothgen_create( calblk_t volatile *pblk )
{
  /* cam/crank channels are fixed, but can be configurable someday: */
  if( FS_ETPU_ERROR_NONE !=
    fs_etpu_toothgen_init( 31,                          /**< crank channel */
                           30,                          /**< cam channel */
                           FS_ETPU_PRIORITY_LOW,
                           (uint8_t)pblk->test.tcnt,    /**< physical teeth */
                           (uint8_t)pblk->test.mtcnt,   /**< missing teeth */
                           (0xffffff*((unsigned)pblk->test.tg_dc))/0xff, /**< duty cycle */
                           1,                           /**< start @ tooth # */
                           pblk->test.rpm,              /**< initial rpm value */
                           etpu_tcr1_freq(),
                           (uint8_t)pblk->test.ctstart, /**< cam start stop teeth */
                           (uint8_t)pblk->test.ctstop) )
  {
    err_push( CODE_TTOOTHGEN_TGINIT );
    return;
  }

  void (*ptask)(void) = 0;
  switch( pblk->test.tg_mode )
  {
    case TGMODE_FIXED:
      ptask = task_toothgen_fixed;
      break;
    case TGMODE_JITTER:
      ptask = task_toothgen_jitter;
      break;
    case TGMODE_CYCLE:
      ptask = task_toothgen_cycle;
      break;
    default:
      err_push( CODE_TTOOTHGEN_TGMODE );
      return;
  }
  if( task_create( ptask, TASKPRI_TOOTHGEN, 0, 0, 0 ) == NO_TID )
    err_push( CODE_TTOOTHGEN_CREATE );
}
