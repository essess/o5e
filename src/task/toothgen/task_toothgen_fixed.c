/**
 * @file       task_toothgen_fixed.c
 * @headerfile task_toothgen_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "task/toothgen/task_toothgen_prv.h"
#include "global.h"
#include "calblk.h"
#include "cal.h"
#include "etpu.h"
#include "etpu/etpu_toothgen.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @internal
 * @brief fixed rpm toothgen control task
 */
void
  task_toothgen_fixed( void )
{
  task_open();
  static uint16_t rpm;            /**< prev commanded rpm */
  static calblk_t volatile *pblk;
  pblk = (calblk_t*)cal_getblk_ptr();
  rpm = pblk->test.rpm;
  err_push( CODE_TTOOTHGEN_TFIXMODE );
  while( pblk )
  {
    if( pblk->test.rpm != rpm )   /**< change in rpm? */
    {
      if( FS_ETPU_ERROR_NONE !=
        fs_etpu_toothgen_adj( 31,
                              (0xffffff*((unsigned)pblk->test.accel))/0xff,
                              pblk->test.rpm,
                              etpu_tcr1_freq()) )
      {
        err_push( CODE_TTOOTHGEN_TFIXADJ );
        task_wait( 5000 );
      }
      rpm = pblk->test.rpm;
    }
    task_wait( 500 );
  }
  task_close();
}
