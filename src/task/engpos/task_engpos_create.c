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

#pragma warn_implicitconv off

/**
 * @public
 * @brief create the engine position task
 * @retval none
 */
void
  task_engpos_create( calblk_t volatile *pblk )
{
  /* pblk has already been validated for us previously */
  if( FS_ETPU_ERROR_NONE !=
    fs_etpu_app_eng_pos_mcam_init(
      1,                            /**< mcam channel */
      FS_ETPU_MCAM_PRIORITY_LOW,    /**< mcam pri */
      pblk->cccfg.cam_edge,         /**< mcam edge polarity */
      pblk->cccfg.defw.camstart,    /**< cam start angle *100 */
      pblk->cccfg.defw.camwidth,    /**< cam window width *100 */
      0,                            /**< crank channel */
      FS_ETPU_CRANK_PRIORITY_HIGH,  /**< crank pri */
      pblk->cccfg.crank_edge,       /**< crank edge polarity */
      pblk->cccfg.teeth,            /**< crank teeth */
      pblk->cccfg.mteeth,           /**< crank missing teeth */
      pblk->cccfg.blanktcnt,        /**< tooth blanking cnt */
      1024,                         /**< tick p/tooth */            // todo: not sure what to do
      pblk->cccfg.defwr.norm,       /**< normal windowing ratio */
      pblk->cccfg.defwr.aftergap,   /**< after gap windowing ratio */
      pblk->cccfg.defwr.acrossgap,  /**< across gap windowing ratio */
      pblk->cccfg.defwr.timeout,    /**< timeout windowing ratio */
      pblk->cccfg.crank_gap_ratio,  /**< gap ratio */
      pblk->cccfg.blankt_ms,        /**< blank time: ms */
      pblk->cccfg.ftto,             /**< first tooth timeout: us */
      0,                            /**< link 1 */
      0,                            /**< link 2 */
      0,                            /**< link 3 */
      0,                            /**< link 4 */
      etpu_tcr1_freq()) )
  {
    err_push( CODE_ENGPOS_EPMINIT );
    return;
  }

  if( task_create( task_engpos, TASKPRI_ENGPOS, 0, 0, 0 ) == NO_TID )
    err_push( CODE_ENGPOS_CREATE );
}

/* --| INTERNAL |--------------------------------------------------------- */