/**
 * @file       fill.c
 * @headerfile util.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "util.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

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
            uint32_t cnt )
{
  err_assert( dst, CODE_UTIL_BFDSTPTR );
  while( cnt ) {
    --cnt;
    dst[cnt] = fill_value;
  }
}

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
            uint32_t cnt )
{
  err_assert( dst, CODE_UTIL_WFDSTPTR );
  err_assert( !((int)dst%sizeof(int)), CODE_UTIL_WFDSTPTRALIGN );
  err_assert( !(cnt%sizeof(int)), CODE_UTIL_WFCNTMODSIZE );
  cnt /= sizeof(uint32_t);
  while( cnt ) {
    --cnt;
    dst[cnt] = fill_value;
  }
}

/* --| INTERNAL |--------------------------------------------------------- */
