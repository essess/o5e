/**
 * @file       led_set.c
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
 * @brief apply passed bitmask to led's
 *        0b000.....1001 => led0:on,led1:off,led2:off,led3:on,...
 * @param[in] bm bitmask
 * @retval none
 */
void
  led_set( unsigned bm )
{
  bm & (1<<0)?__led_on(0):__led_off(0);
  bm & (1<<1)?__led_on(1):__led_off(1);
  bm & (1<<2)?__led_on(2):__led_off(2);
  bm & (1<<3)?__led_on(3):__led_off(3);
}
