/**
 * @file   global.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __global_h
#define   __global_h

#include <stdint.h>
#include "err.h"

/* --| INTERNAL |--------------------------------------------------------- */

typedef struct
{
  uint16_t rpm;
  struct {
    uint16_t pot;     /**< mv    */
    uint16_t map;     /**< mv    */
    uint16_t clt;     /**< mv    */
    uint16_t mat;     /**< mv    */
    uint16_t tps;     /**< mv    */
    uint16_t m1;      /**< mv    */
    uint16_t m2;      /**< mv    */
    uint16_t m3;      /**< mv    */
    uint16_t m4;      /**< mv    */
    uint16_t m5;      /**< mv    */
    uint16_t uctemp;  /**< ticks */
  } unfiltered;
} global_t;

extern volatile global_t global;

#define MV_MAX          (5000)
#define MV_MIN          (0)
#define is_mv(x_)       ((x_>=MV_MIN)&&(x_<=MV_MAX))

#define RPM_MAX         (24000)
#define RPM_MIN         (0)
#define is_rpm(x_)      ((x_>=RPM_MIN)&&(x_<=RPM_MAX))

#define TICKS_MAX       (0xFFF)
#define TICKS_MIN       (0x000)
#define is_ticks(x_)    ((x_>=TICKS_MIN)&&(x_<=TICKS_MAX))

/* --| PUBLIC   |--------------------------------------------------------- */
/* ONLY use the following to manipulate globals: */
/* static inline g<op>_<member>_<units>()        */

static inline void
  gset_unfpot_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUPOT );
  global.unfiltered.pot = mv;
}

static inline uint16_t
  gget_unfpot_mv( void )
{ return global.unfiltered.pot; }

/* -------------------------- */

static inline void
  gset_rpm( uint16_t rpm )
{
  err_assert( is_rpm(rpm), CODE_MISC_GSRPM );
  global.rpm = rpm;
}

static inline uint16_t
  gget_rpm( void )
{ return global.rpm; }

/* -------------------------- */

static inline void
  gset_unfmap_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUMAP );
  global.unfiltered.map = mv;
}

static inline uint16_t
  gget_unfmap_mv( void )
{ return global.unfiltered.map; }

/* -------------------------- */

static inline void
  gset_unfclt_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUCLT );
  global.unfiltered.clt = mv;
}

static inline uint16_t
  gget_unfclt_mv( void )
{ return global.unfiltered.clt; }

/* -------------------------- */

static inline void
  gset_unfmat_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUMAT );
  global.unfiltered.mat = mv;
}

static inline uint16_t
  gget_unfmat_mv( void )
{ return global.unfiltered.mat; }

/* -------------------------- */

static inline void
  gset_unftps_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUTPS );
  global.unfiltered.tps = mv;
}

static inline uint16_t
  gget_unftps_mv( void )
{ return global.unfiltered.tps; }

/* -------------------------- */

static inline void
  gset_unfm1_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUM1 );
  global.unfiltered.m1 = mv;
}

static inline uint16_t
  gget_unfm1_mv( void )
{ return global.unfiltered.m1; }

/* -------------------------- */

static inline void
  gset_unfm2_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUM2 );
  global.unfiltered.m2 = mv;
}

static inline uint16_t
  gget_unfm2_mv( void )
{ return global.unfiltered.m2; }

/* -------------------------- */

static inline void
  gset_unfm3_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUM3 );
  global.unfiltered.m3 = mv;
}

static inline uint16_t
  gget_unfm3_mv( void )
{ return global.unfiltered.m3; }

/* -------------------------- */

static inline void
  gset_unfm4_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUM4 );
  global.unfiltered.m4 = mv;
}

static inline uint16_t
  gget_unfm4_mv( void )
{ return global.unfiltered.m4; }

/* -------------------------- */

static inline void
  gset_unfm5_mv( uint16_t mv )
{
  err_assert( is_mv(mv), CODE_MISC_GSUM5 );
  global.unfiltered.m5 = mv;
}

static inline uint16_t
  gget_unfm5_mv( void )
{ return global.unfiltered.m5; }

/* -------------------------- */

static inline void
  gset_unfuctemp_ticks( uint16_t ticks )
{
  err_assert( is_ticks(ticks), CODE_MISC_GSUUCTEMP );
  global.unfiltered.uctemp = ticks;
}

static inline uint16_t
  gget_unfuctemp_ticks( void )
{ return global.unfiltered.uctemp; }

#endif // __global_h
