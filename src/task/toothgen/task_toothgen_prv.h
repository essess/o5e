/**
 * @file   task_toothgen_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_toothgen_prv_h
#define   __task_toothgen_prv_h

/**
 * @internal
 * @brief fixed rpm toothgen control task
 */
void
  task_toothgen_fixed( void );

/**
 * @internal
 * @brief jittered rpm toothgen control task
 */
void
  task_toothgen_jitter( void );

/**
 * @internal
 * @brief cyclic rpm toothgen control task
 */
void
  task_toothgen_cycle( void );

#endif // __task_toothgen_prv_h