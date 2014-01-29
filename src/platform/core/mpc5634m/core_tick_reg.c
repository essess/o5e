/**
 * @file       core_tick_reg.c
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
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief register application tick handler
 * @param[in] fptr tick handler callback
 * @retval none
 */
void
  core_tick_reg( void (*fptr)(void) )
{
  tick_handler = fptr ? fptr : tick_handler ;
}

/* --| INTERNAL |--------------------------------------------------------- */
