/**
 * @file       task_engpos_create.c
 * @headerfile task_engpos.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "err.h"
#include "task/task_engpos.h"
#include "task/engpos/task_engpos_prv.h"
#include "etpu.h"
#include "etpu/etpu_util.h"
#include "etpu/etpu_app_eng_pos_mcam.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create the engine position task
 * @retval none
 */
void
  task_engpos_create( void )
{
  // todo: pull cfg from newly created items in cal
  if( FS_ETPU_ERROR_NONE !=
    fs_etpu_app_eng_pos_mcam_init(
      1,                            /**< mcam channel */
      FS_ETPU_MCAM_PRIORITY_LOW,    /**< mcam pri */
      FS_ETPU_MCAM_FM0_RISING_EDGE, /**< mcam edge polarity */
      48000,                        /**< cam start angle *100 */
      9000,                         /**< cam window width *100 */
      0,                            /**< crank channel */
      FS_ETPU_CRANK_PRIORITY_HIGH,  /**< crank pri */
      FS_ETPU_CRANK_FM0_RISING_EDGE,/**< crank edge polarity */
      35,                           /**< crank teeth */
      1,                            /**< crank missing teeth */
      4,                            /**< tooth blanking cnt */
      1024,                         /**< tick p/tooth */            // todo: not sure what to do
      0xffffff/2,                   /**< normal windowing ratio */  // todo:cfg (table lookup)
      0xffffff/2,                   /**< after gap windowing ratio */ // todo:cfg (table lookup)
      0xffffff/2,                   /**< across gap windowing ratio */ // todo:cfg (table lookup)
      0xffffff/2,                   /**< timeout windowing ratio */ // todo:cfg (table lookup)
      0xffffff/2,                   /**< gap ratio */               // todo:cfg
      100,                          /**< blank time: ms */
      400,                          /**< first tooth timeout: us */
      0,                            /**< link 1 */                  // todo:cfg?
      0,                            /**< link 2 */                  // todo:cfg?
      0,                            /**< link 3 */                  // todo:cfg?
      0,                            /**< link 4 */                  // todo:cfg?
      etpu_tcr1_freq()) )
  {
    err_push( CODE_ENGPOS_EPMINIT );
    return;
  }

  if( task_create( task_engpos, TASKPRI_ENGPOS, 0, 0, 0 ) == NO_TID )
    err_push( CODE_ENGPOS_CREATE );
}

/* --| INTERNAL |--------------------------------------------------------- */