/**
 * @file       task_toothgen_cycle.c
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
 * @brief cyclic rpm toothgen control task
 */
void
  task_toothgen_cycle( void )
{
  task_open();
  static calblk_t volatile *pblk;
  pblk = (calblk_t*)cal_getblk_ptr();
  err_push( CODE_TTOOTHGEN_TCYCMODE );
  while( pblk )
  {
    if( FS_ETPU_ERROR_NONE !=
      fs_etpu_toothgen_adj( 31,   /**< step 0 */
                            (0xffffff*((unsigned)pblk->test.caccel0))/0xff,
                            pblk->test.crpm0,
                            etpu_tcr1_freq()) )
    {
      err_push( CODE_TTOOTHGEN_TCYC0ADJ );
      task_wait( 5000 );
    }
    task_wait( (uint16_t)pblk->test.cdwell0 );
    if( FS_ETPU_ERROR_NONE !=
      fs_etpu_toothgen_adj( 31,   /**< step 1 */
                            (0xffffff*((unsigned)pblk->test.caccel1))/0xff,
                            pblk->test.crpm1,
                            etpu_tcr1_freq()) )
    {
      err_push( CODE_TTOOTHGEN_TCYC1ADJ );
      task_wait( 5000 );
    }
    task_wait( (uint16_t)pblk->test.cdwell1 );
    if( FS_ETPU_ERROR_NONE !=
      fs_etpu_toothgen_adj( 31,   /**< step 2 */
                            (0xffffff*((unsigned)pblk->test.caccel2))/0xff,
                            pblk->test.crpm2,
                            etpu_tcr1_freq()) )
    {
      err_push( CODE_TTOOTHGEN_TCYC2ADJ );
      task_wait( 5000 );
    }
    task_wait( (uint16_t)pblk->test.cdwell2 );
    if( FS_ETPU_ERROR_NONE !=
      fs_etpu_toothgen_adj( 31,   /**< step 3 */
                            (0xffffff*((unsigned)pblk->test.caccel3))/0xff,
                            pblk->test.crpm3,
                            etpu_tcr1_freq()) )
    {
      err_push( CODE_TTOOTHGEN_TCYC3ADJ );
      task_wait( 5000 );
    }
    task_wait( (uint16_t)pblk->test.cdwell3 );
  }
  task_close();
}
