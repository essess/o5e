/**
 * @file   core.h
 * @author sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __core_h
#define   __core_h

#include <stdint.h>

#define core_declare_state(s_)         register int s_
#define core_restore_state(s_)         asm { wrtee  s_; }
#define core_disable_interrupts(s_)    asm { mfmsr  s_; \
                                             wrteei 0; }

/**
 * @public
 * @brief hard reset the core while asserting the external line also
 * @param none
 * @retval none
 */
void
  core_reset( void );

/**
 * @public
 * @brief register application tick handler
 * @param[in] fptr tick handler callback
 * @retval none
 */
void
  core_tick_reg( void (*fptr)(void) );

/**
 * @public
 * @brief start ALL timebases
 * @param none
 * @retval none
 */
void
  core_start_timers( void );

/**
 * @public
 * @brief atomic fetch of entire timebase
 * @note runs at core clock frequency
 * @retval uint64_t current time
 */
uint64_t
  core_get_timebase( void );

/**
 * @public
 * @brief fetch only the lower half of the complete timebase
 * @note runs at core clock frequency
 * @retval uint32_t current time
 */
uint32_t
  core_get_timebase_lower( void );

/**
 * @public
 * @brief fetch system millisecond counter
 * @retval uint32_t milliseconds since powerup
 */
uint32_t
  core_get_systime( void );

#endif // __core_h
