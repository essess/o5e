/**
 * @file   task_tuner_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_tuner_prv_h
#define   __task_tuner_prv_h

#include "task/task_tuner.h"
#include <stdint.h>

/**
 * @internal
 * @brief tuner studio error codes
 */
enum
{
  OK                 = 0x00,
  BAD_CRC            = 0x82,
  UNHANDLED_CMD      = 0x83,
  OUT_OF_RANGE       = 0x84,
  SEQUENCE_FAILURE_2 = 0x88
};

/* max size of a page, more of a logical divsion than */
/* a physical division.                               */
#define PAGE_BYTESIZE (4*1024u)

/**
 * @internal
 * @brief tuner studio i/o task
 */
void
  task_tuner( void );

/**
 * @internal
 * @brief get a bounds checked block reference into the calibration space
 * @param[in] offset byte offset into calibration
 * @param[in] bytesize expected byte size of access to be performed upon the
 *                     return reference (internal limit checking performed)
 * @retval uint8_t* absolute reference, null if bound check fails
 */
uint8_t *
  getcalblk_ptr_byoffset( unsigned offset,
                          unsigned bytesize );

/**
 * @internal
 * @brief pop an error code off the stack
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_p( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief unhandled, but correctly formed '001' cmd, rolled in from the tuner
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_unh( uint8_t *pbuff,
               uint16_t len );

/**
 * @internal
 * @brief request output channels
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_A( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief query
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_Q( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief signature
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_S( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief write
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_w( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief read
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_r( uint8_t *pbuff,
             uint16_t len );

/**
 * @internal
 * @brief crc a block
 * @param[in/out] pbuff buffer reference
 * @param[in] len byte size of input buffer data
 * @retval uint16_t byte size of return buffer data
 */
uint16_t
  process_k( uint8_t *pbuff,
             uint16_t len );

#endif // __task_tuner_prv_h
