/**
 * @file   task_ana.h
 * @author sstasiak
 * @brief  take raw analog conversions and convert them to engineering units
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_ana_h
#define   __task_ana_h

#include "calblk.h"

#define TASKPRI_ANA (40)

/**
 * @public
 * @brief create and initialize the analog processing task
 * @retval none
 */
void
  task_ana_create( calblk_t volatile *pblk );

#endif // __task_ana_h
