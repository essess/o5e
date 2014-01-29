/**
 * @file   ana.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __ana_h
#define   __ana_h

#include "typedefs.h"

/**
 * @public
 * @enum ana_src_t
 * @brief analog sources
 */
typedef enum
{
  AS_POT  = 0,
  AS_MAP  = 1,
  AS_CLT  = 2,
  AS_MAT  = 3,
  AS_TPS  = 4,
  AS_M1   = 5,
  AS_M2   = 6,
  AS_M3   = 7,
  AS_M4   = 8,
  AS_M5   = 9,
  AS_TEMP = 10,
  AS_SIZE = 11
} ana_src_t;

/**
 * @public
 * @enum ana_evt_t
 * @brief ana events
 */
typedef enum
{
  AE_READY,     /**< conversion complete, samples updated */
  AE_ERRCFIFO,  /**< internal error */
  AE_ERRRFIFO,  /**< internal error */
  AE_UNK
} ana_evt_t;

/**
 * @public
 * @typedef ana_evt_cb_t
 * @brief synchronizing method called when all samples have been updated
 */
typedef void (ana_evt_cb_t)(ana_evt_t);

/**
 * @public
 * @brief helper for caller asserts
 */
static inline int
  is_ana_src( ana_src_t s )
{
  return (s == AS_POT) || (s == AS_MAP) || (s == AS_CLT) || \
         (s == AS_MAT) || (s == AS_TPS) || (s == AS_M1)  || \
         (s == AS_M2)  || (s == AS_M3)  || (s == AS_M4)  || \
         (s == AS_M5)  || (s == AS_TEMP);
}

/**
 * @public
 * @brief initialize analog subsystem
 * @param[in] rate desired sample rate in Hz (50->1000Hz inclusive)
 * @param[in] pf conversion done callback, callers signal that samples
 *               have been updated
 * @retval uint16_t* reference to sample array indexed by @see { ana_src_t }
 *                   or null on failure
 * @note all channels are updated at the same rate
 */
vuint16_t const *
  ana_init( uint32_t rate,
            ana_evt_cb_t *pf );

/**
 * @public
 * @brief kickoff channel sampling
 * @param none
 * @retval none
 */
void
  ana_start( void );

/**
 * @public
 * @brief convert raw samples to ticks
 * @param[in] raw raw analog sample
 * @retval uint16_t ticks
 */
static inline uint16_t
  ana_raw_to_ticks( uint16_t raw )
{
  return raw>>2;
}

/**
 * @public
 * @brief convert raw (unadjusted) samples to millivolts
 * @param[in] raw raw analog sample
 * @retval uint16_t millivolts
 */
static inline uint16_t
  ana_raw_to_mv( uint16_t raw )
{
  return (5000*ana_raw_to_ticks(raw)/0xfff);
}

#endif // __ana_h
