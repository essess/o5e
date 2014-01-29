/**
 * @file   led.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __led_h
#define   __led_h

/**
 * @public
 * @brief init all leds to default state
 * @param none
 * @retval none
 */
void
  led_init( void );

/**
 * @public
 * @brief turn on led
 * @param[in] l desired led
 * @retval none
 */
void
  led_on( unsigned l );

/**
 * @public
 * @brief turn off led
 * @param[in] l desired led
 * @retval none
 */
void
  led_off( unsigned l );

/**
 * @public
 * @brief invert led state
 * @param[in] l desired led
 * @retval none
 */
void
  led_invert( unsigned l );

/**
 * @public
 * @brief apply passed bitmask to led's
 *        0b000.....1001 => led0:on,led1:off,led2:off,led3:on,...
 * @param[in] bm bitmask
 * @retval none
 */
void
  led_set( unsigned bm );

#endif // __led_h
