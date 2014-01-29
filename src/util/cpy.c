/**
 * @file       cpy.c
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
 * @brief brute force byte copy
 * @param[in] dst destination reference
 * @param[in] src source reference
 * @param[in] cnt byte count
 * @retval none
 */
void
  bytecpy( uint8_t *dst,
           uint8_t const *src,
           uint32_t cnt )
{
  err_assert( src, CODE_UTIL_BCSRCPTR );
  err_assert( dst, CODE_UTIL_BCDSTPTR );
  while( cnt ) {
    --cnt;
    dst[cnt] = src[cnt];
  }
}

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
           uint32_t cnt )
{
  err_assert( src, CODE_UTIL_WCSRCPTR );
  err_assert( dst, CODE_UTIL_WCDSTPTR );
  err_assert( !((int)src%sizeof(int)), CODE_UTIL_WCSRCPTRALIGN );
  err_assert( !((int)dst%sizeof(int)), CODE_UTIL_WCDSTPTRALIGN );
  err_assert( !(cnt%sizeof(int)), CODE_UTIL_WCCNTMODSIZE );
  cnt /= sizeof(uint32_t);
  while( cnt ) {
    --cnt;
    dst[cnt] = src[cnt];
  }
}

/* --| INTERNAL |--------------------------------------------------------- */
