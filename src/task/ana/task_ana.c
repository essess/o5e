/**
 * @file       task_ana.c
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
#include "err.h"
#include "ana.h"
#include "global.h"

#define SAMPLE_RATE 200   /**< fixed to 200hz for now */

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

static void ana_cb( ana_evt_t );
static void process0( void );
static void process1( void );
static void process2( void );
static vuint16_t const *psamples;
static Sem_t rdy;

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief analog processing task
 */
void
  task_ana( void )
{
  task_open();
  rdy = sem_bin_create( 0 );
  psamples = ana_init( SAMPLE_RATE, ana_cb );
  if( psamples && (rdy != NO_SEM) )
  {
    task_wait( 10 );      /**< REFBYPC cap needs 8+ms to stabilize after */
    ana_start();          /*   ADC powerup                               */
    do
    {
      sem_wait( rdy );
      process0();         /**< to keep latencies low, sample processing  */
      OS_SCHEDULE;        /*   is divided into multiple stages           */
      process1();
      OS_SCHEDULE;
      process2();
    } while( psamples );
  }
  err_push( CODE_TANA_SPTRSEM );
  task_close();
}

/* --| INTERNAL |--------------------------------------------------------- */

/* @brief stage 0 processing */
static void
  process0( void )
{
  /* store off unfiltered samples: */
  gset_unfpot_mv( ana_raw_to_mv(psamples[AS_POT]) );
  gset_unfmap_mv( ana_raw_to_mv(psamples[AS_MAP]) );
  gset_unfclt_mv( ana_raw_to_mv(psamples[AS_CLT]) );
  gset_unfmat_mv( ana_raw_to_mv(psamples[AS_MAT]) );
  gset_unftps_mv( ana_raw_to_mv(psamples[AS_TPS]) );
  gset_unfm1_mv( ana_raw_to_mv(psamples[AS_M1]) );
  gset_unfm2_mv( ana_raw_to_mv(psamples[AS_M2]) );
  gset_unfm3_mv( ana_raw_to_mv(psamples[AS_M3]) );
  gset_unfm4_mv( ana_raw_to_mv(psamples[AS_M4]) );
  gset_unfm5_mv( ana_raw_to_mv(psamples[AS_M5]) );
  gset_unfuctemp_ticks( ana_raw_to_ticks(psamples[AS_TEMP]) );
}

/* @brief stage 1 processing */
static void
  process1( void )
{
  /* do some filtering: */
  /* NOTE: just because we have this opportunity to do filtering doesn't    */
  /*       mean that we have to do ALL filtering here. it may be smarter    */
  /*       to do filtering at the point of use and 'push back' the filtered */
  /*       value into globals to be sent out to the tuner later             */
}

/* @brief stage 2 processing */
static void
  process2( void )
{
  /* do some filtering: */
  /* NOTE: just because we have this opportunity to do filtering doesn't    */
  /*       mean that we have to do ALL filtering here. it may be smarter    */
  /*       to do filtering at the point of use and 'push back' the filtered */
  /*       value into globals to be sent out to the tuner later             */
}

/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief ana callback handler
 */
static void
  ana_cb( ana_evt_t e )
{
  switch( e )
  {
    case AE_READY:
      sem_ISR_signal( rdy );
      break;
    case AE_ERRCFIFO:
      err_push( CODE_TANA_ERRCFIFO );
      break;
    case AE_ERRRFIFO:
      err_push( CODE_TANA_ERRRFIFO );
      break;
    default:
      err_push( CODE_TANA_UNKEVT );
  }
}
