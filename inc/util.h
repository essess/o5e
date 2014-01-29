/**
 * @file   util.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __util_h
#define   __util_h

#include <stdint.h>

/**
 * @public
 * @brief perform a crc on the passed buffer
 * @param[in] in_crc carryover crc, from last computation if doing large blocks
 * @param[in] buf byte buffer to crc
 * @param[in] cnt buf byte size
 * @retval uint32_t crc32
 */
uint32_t
  crc32( uint32_t in_crc,
         uint8_t const *buf,
         uint32_t cnt );

/**
 * @public
 * @brief brute force byte copy
 * @param[in] dst destination reference
 * @param[in] src source reference
 * @param[in] cnt byte count
 * @retval none
 */
void
  bytecpy( uint8_t *dst,
           uint8_t const *src,
           uint32_t cnt );

/**
 * @public
 * @brief brute force byte fill
 * @param[in] dst destination reference
 * @param[in] fill_value fill value
 * @param[in] cnt byte count
 * @retval none
 */
void
  bytefill( uint8_t *dst,
            uint8_t fill_value,
            uint32_t cnt );

/**
 * @public
 * @brief brute force ALIGNED word copy
 * @param[in] dst destination reference
 * @param[in] src source reference
 * @param[in] cnt byte count
 * @retval none
 */
void
  wordcpy( uint32_t *dst,
           uint32_t const *src,
           uint32_t cnt );

/**
 * @public
 * @brief brute force ALIGNED word fill
 * @param[in] dst destination reference
 * @param[in] fill_value fill value
 * @param[in] cnt byte count
 * @retval none
 */
void
  wordfill( uint32_t *dst,
            uint32_t fill_value,
            uint32_t cnt );

#endif // __util_h
