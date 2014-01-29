/**
 * @file   task_err.h
 * @author sstasiak
 * @brief  hook and display the topmost error from the err api
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __task_err_h
#define   __task_err_h

#define TASKPRI_ERR (250)

/**
 * @public
 * @brief create and initialzie the error display task
 * @retval none
 */
void
  task_err_create( void );

#endif // __task_err_h
