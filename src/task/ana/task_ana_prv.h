/**
 * @file   task_ana_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_ana_prv_h
#define   __task_ana_prv_h

#include "task/task_ana.h"

/**
 * @internal
 * @brief analog processing task
 */
void
  task_ana( void );

/**
 * @internal
 * @brief analog spoof/testing task
 */
void
  task_ana_test( void );

#endif // __task_ana_prv_h