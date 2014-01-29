/**
 * @file   cal.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __cal_h
#define   __cal_h

/**
 * @public
 * @brief load a volatile cal block from storage
 * @param none
 * @retval int !0 on success
 * @note { not threadsafe }
 */
int
  cal_init( void );

/**
 * @public
 * @brief get a reference to the volatile calibration block
 * @param none
 * @retval uint8_t* reference
 */
uint8_t *
  cal_getblk_ptr( void );

/**
 * @public
 * @brief get the byte size of the volatile calibration block
 * @param none
 * @retval unsigned byte size of block
 */
unsigned
  cal_getblk_bytesize( void );

/**
 * @public
 * @enum ccs_t
 * @brief cal commit states:
 *        idle->erase->write->idle
 */
typedef enum
{
  CCS_IDLE,
  CCS_ERASE,
  CCS_WRITE,

  CCS_ERROR
} ccs_t;

/**
 * @public
 * @brief begin operation which commits the volatile cal block back to
 *        storage
 * @attention DO NOT MODIFY the cal block while a commit operation is
 *            in progress
 * @param none
 * @retval ccs_t current state of operation
 */
ccs_t
  cal_commit( void );

/**
 * @public
 * @brief poll commit operation started by @see { cal_commit }
 * @param none
 * @retval ccs_t current state of operation, CCS_IDLE when complete
 */
ccs_t
  cal_commit_chk( void );

#endif // __cal_h
