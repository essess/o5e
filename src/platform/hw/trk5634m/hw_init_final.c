/**
 * @file       hw_init_final.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/cstart.h"
#include "led.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief Final opportunity to initalize hardware specific items before
 *        dropping into main()
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * you can: depend on the crt being 'up'
 */
__declspec( section ".init" )
void
  hw_init_final( void )
{
  led_init();
  led_on( LED_CPU_BUSY );
}

/* --| INTERNAL |--------------------------------------------------------- */
