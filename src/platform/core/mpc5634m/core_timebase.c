/**
 * @file       core_timebase.c
 * @headerfile core.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "core.h"
#include "platform/core/mpc5634m/core_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * timebase sfrs - see bug note below
 */
enum
{
  TIMEBASE_LOWER = 268,
  TIMEBASE_UPPER = 269
};

/**
 * @public
 * @brief atomic fetch of entire timebase
 * @note runs at core clock frequency
 * @retval uint64_t current time
 */
asm uint64_t
  core_get_timebase( void )
{
  nofralloc
// mwerks bug ?
// the following sequence does not generate the
// correct opcodes:
//
//  mftbu   r3
//  mftb    r4
//  mftbu   r5
//
//  they show up as illegal opcodes in the disassembler
//  so I had to manually specify the sfr values:
//
//  mfspr   r3, 269 -> TIMEBASE_UPPER
//  mfspr   r4, 268 -> TIMEBASE_LOWER
//  mfspr   r5, 269 -> TIMEBASE_UPPER
@loop:
  mfspr   r3, TIMEBASE_UPPER
  mfspr   r4, TIMEBASE_LOWER
  mfspr   r5, TIMEBASE_UPPER
  cmpw    r5, r3    // did upper roll ?
  bne+    @loop     // ... then lower is wrong
  blr
}

/**
 * @public
 * @brief fetch only the lower half of the complete timebase
 * @note runs at core clock frequency
 * @retval uint32_t current time
 */
asm uint32_t
  core_get_timebase_lower( void )
{
  nofralloc
  mfspr   r3, TIMEBASE_LOWER
  blr
}

/**
 * @public
 * @brief fetch system millisecond counter
 * @retval uint32_t milliseconds since powerup
 */
inline uint32_t
  core_get_systime( void )
{
  return systime;
}
