/**
 * @file       ana_prv.c
 * @headerfile ana_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/ana/ana_prv.h"

/* standard conversion command helpers: */
#define CAL(x_)       ((x_&1u)<<24)
#define MSG_TAG(x_)   ((x_&0xfu)<<20)
#define LST(x_)       ((x_&0x3u)<<18)
#define TSR(x_)       ((x_&1u)<<17)
#define FMT(x_)       ((x_&1u)<<16)
#define CHAN_NUM(x_)  ((x_&0xff)<<8)

#define RFIFO5        (5)
#define SAMP8         (1) /* fyi: 10MHz/14+8 = ~2.2us btwn conv = ~450KHz */

/**
 * @internal
 * @brief analog source channels
 */
typedef enum
{
  POT  = 17,
  MAP  = 35,
  CLT  = 34,
  MAT  = 33,
  TPS  = 32,
  M1   = 31,
  M2   = 30,
  M3   = 28,
  M4   = 27,
  M5   = 25,
  TEMP = 128
};

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief predefined command queue
 * @note notice it's in RAM, I've disabled dma access to the flash array
 *       as a design decision
 */
uint32_t cmd_queue[AS_SIZE] =
{
  [AS_POT]  = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(POT),
  [AS_MAP]  = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(MAP),
  [AS_CLT]  = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(CLT),
  [AS_MAT]  = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(MAT),
  [AS_TPS]  = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(TPS),
  [AS_M1]   = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(M1),
  [AS_M2]   = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(M2),
  [AS_M3]   = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(M3),
  [AS_M4]   = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(M4),
  [AS_M5]   = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(M5),
  [AS_TEMP] = MSG_TAG(RFIFO5) | BN(1) | LST(SAMP8) | CHAN_NUM(TEMP) | PAUSE,
};