/**
 * @file   task_toothgen.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_toothgen_h
#define   __task_toothgen_h

#include "calblk.h"

#define TASKPRI_TOOTHGEN (245)

/**
 * @public
 * @brief create the toothgen control task
 */
void
  task_toothgen_create( calblk_t volatile *pblk );

#endif // __task_toothgen_h