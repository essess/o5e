/**
 * @file       led_off.c
 * @headerfile led.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "led.h"
#include "platform/hw/trk5634m/led/led_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief turn off led
 * @param[in] l desired led
 * @retval none
 */
void
  led_off( unsigned l )
{
  if( l <= LEDCNT )
    __led_off( l );
}
