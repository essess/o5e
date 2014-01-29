/**
 * @file       hw_init.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/cstart.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief Startup hook called first thing out of reset following core_init().
 *        Use this to get any hardware specific functionality turned
 *        on/off/reset asap
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * you can: use any register for temp storage freely
 * you can: use sram freely
 * try to: make your way through as fast as possible
 * try to: use asm - the crt is not available for you
 */
__declspec( section ".init" )
asm void
  hw_init( void )
{
        nofralloc
        blr
}

/* --| INTERNAL |--------------------------------------------------------- */
