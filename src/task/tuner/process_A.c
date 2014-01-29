/**
 * @file       process_A.c
 * @headerfile task_tuner_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/tuner/task_tuner_prv.h"
#include "err.h"
#include "global.h"
#include "core.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief request output channels
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_A( uint8_t *pbuff,
             uint16_t len )
{
  err_assert( pbuff, CODE_TUNER_PAPTR );
  err_assert( *pbuff == 'A', CODE_TUNER_PACMD );
  err_assert( len == 1, CODE_TUNER_PALEN );

  #pragma push
  #pragma pack(1)
  typedef struct
  {
    uint8_t  status;
    uint32_t systime;   /**< msec  */
    uint16_t rpm;       /**< rpm   */
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
  } reply_t;
  #pragma pop

  reply_t *const reply = (reply_t*)pbuff;
  reply->status = OK;

  reply->systime = core_get_systime();
  reply->rpm = gget_rpm();
  reply->unfiltered.pot = gget_unfpot_mv();
  reply->unfiltered.map = gget_unfmap_mv();
  reply->unfiltered.clt = gget_unfclt_mv();
  reply->unfiltered.mat = gget_unfmat_mv();
  reply->unfiltered.tps = gget_unftps_mv();
  reply->unfiltered.m1 = gget_unfm1_mv();
  reply->unfiltered.m2 = gget_unfm2_mv();
  reply->unfiltered.m3 = gget_unfm3_mv();
  reply->unfiltered.m4 = gget_unfm4_mv();
  reply->unfiltered.m5 = gget_unfm5_mv();
  reply->unfiltered.uctemp = gget_unfuctemp_ticks();

  return sizeof(reply_t);
}