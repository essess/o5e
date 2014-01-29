/**
 * @file   task_tuner.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_tuner_h
#define   __task_tuner_h

#define TASKPRI_TUNER (240)

/**
 * @public
 * @brief create the tuner i/o task
 * @retval none
 */
void
  task_tuner_create( void );

#endif // __task_tuner_h
