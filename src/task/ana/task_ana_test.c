/**
 * @file       task_ana_test.c
 * @headerfile task_ana_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/ana/task_ana_prv.h"
#include "cocoos.h"
#include "global.h"
#include "calblk.h"
#include "cal.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief analog spoof/testing task
 */
void
  task_ana_test( void )
{
  task_open();
  static calblk_t volatile *pblk;
  pblk = (calblk_t*)cal_getblk_ptr();
  while( pblk )
  {
    gset_unfpot_mv( pblk->test.pot );
    gset_unfmap_mv( pblk->test.map );
    gset_unfclt_mv( pblk->test.clt );
    gset_unfmat_mv( pblk->test.mat );
    gset_unftps_mv( pblk->test.tps );
    gset_unfm1_mv( pblk->test.m1 );
    gset_unfm2_mv( pblk->test.m2 );
    gset_unfm3_mv( pblk->test.m3 );
    gset_unfm4_mv( pblk->test.m4 );
    gset_unfm5_mv( pblk->test.m5 );
    task_wait( 500 ); /**< 2Hz should be fine until proven otherwise */
  };
  task_close();
}