/**
 * @file   cal_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __cal_prv_h
#define   __cal_prv_h

#include <stdint.h>
#include "cal.h"
#include "flash.h"

typedef struct
{
  flash_t *pflash;
  ccs_t state;
} cal_t;

extern cal_t cal;

/**
 * @internal
 * @brief get absolute start address of entire volatile calibration block
 * @param none
 * @retval uint8_t* calibration block reference
 */
uint8_t *
  cal_ptr( void );

/**
 * @internal
 * @brief get byte size of entire volatile calibration block
 * @param none
 * @retval unsigned size of volatile calibration block in bytes
 */
unsigned
  cal_bytesize( void );

/**
 * @internal
 * @union resv_overlay_t cal_prv.h
 * @brief cal reserved space overlay
 */
typedef union
{
  uint64_t uint64[2];   /* force dword multiple width */
  struct
  {
    uint32_t crc;       /* uint64[0] */
    uint32_t _pad_;
    uint64_t is_valid;  /* uint64[1] */
  };
} resv_overlay_t;

/**
 * @internal
 * @brief return the size of the reserved segment in bytes
 * @param none
 * @retval unsigned byte size of reserved block
 */
static inline unsigned
  resv_bytesize( void )
{
  return sizeof(resv_overlay_t);
}

/**
 * @internal
 * @brief return the size of the data segment in bytes
 * @param none
 * @retval unsigned byte size of data block
 */
static inline unsigned
  data_bytesize( void )
{
  return cal_bytesize()-resv_bytesize();
}

/**
 * @internal
 * @brief return the relative block offset of the reserved section
 * @param none
 * @retval unsigned offset in bytes
 */
static inline unsigned
  resv_offset( void )
{
  return data_bytesize();
}

/**
 * @internal
 * @brief return the relative block offset of the data section
 * @param none
 * @retval unsigned offset in bytes
 */
static inline unsigned
  data_offset( void )
{
  return 0;
}

/**
 * @internal
 * @brief given a block ptr, adjust to ptr to point into the data segment
 *        of the passed block
 * @param[in] p raw pointer to a block
 * @retval uint8_t* ptr to the data segment of block
 */
static inline uint8_t *
  data_ptr( uint8_t *p )
{
  return &p[data_offset()];
}

/**
 * @internal
 * @brief given a block ptr, adjust to ptr to point into the reserved segment
 *        of the passed block
 * @param[in] p raw pointer to a block
 * @retval uint8_t* ptr to the reserved segment of block
 */
static inline uint8_t *
  resv_ptr( uint8_t *p )
{
  return &p[resv_offset()];
}

/**
 * @internal
 * @brief find first valid cal in flash and load to volatile calibration space
 * @param[in] pflash flash context
 * @retval int 0 if flash contains no valid data, in that case, volatile cal
 *             space will be initialized w/0xff's
 */
int
  cal_load( flash_t *pflash );

#endif // __cal_prv_h
