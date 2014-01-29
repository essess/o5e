/**
 * @file       cstart.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/cstart.h"
#include "core.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief o5e c application hard reset entry point
 * @param[in] none
 * @param[out] none
 * @retval none
 */
__declspec( vle_off )
__declspec( section ".init" )
asm void
  cstart( void ) __attribute__((noreturn))
{
        extern void main( void );
        nofralloc
        bl      core_init
        bl      hw_init
        bl      crt_init
        bl      hw_init_final
        bl      core_init_final
        bl      main
        b       core_reset
}

/* --| INTERNAL |--------------------------------------------------------- */
