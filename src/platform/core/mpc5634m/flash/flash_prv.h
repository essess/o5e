/**
 * @file   flash_prv.h
 * @author sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __flash_prv_h
#define   __flash_prv_h

#include "flash.h"

/**
 * @internal
 * @brief array states
 */
typedef enum
{
  FLSTATE_IDLE = 0,   /**< array outside of _begin/_end pair         */
  FLSTATE_READY,      /**< waiting to begin write or erase cycle     */
  FLSTATE_BUSY        /**< erase or write cycle is currently pending */
} flash_state_t;

/**
 * @internal
 * @brief driver flash context
 */
struct flash_t
{
  flash_state_t state;
  void const* blkptr;
};

extern flash_t f;

/**
 * @internal
 * @brief block helpers
 */
#define BLK4              ((void const*)0x20000)
#define BLK5              ((void const*)0x30000)
#define BLKSIZE           (64*1024u)
#define LMLR_PW           0xa1a11111
#define SLMLR_PW          0xc3c33333
#define BLKBM_BYADDR(b)   ((b==BLK4)?(1ul<<6):(1ul<<7))

#endif // __flash_prv_h
