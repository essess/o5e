/**
 * @file   led_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __led_prv_h
#define   __led_prv_h

#include "platform/core/mpc5634m/mpc5634m.h"

#define LEDCNT  (3)     /**< trk5634m has 4 leds, designated as 0->3       */
#define LEDBASE (188)   /**< siu base index                                */

/**
 * @internal
 */
static inline void
  __led_on( unsigned l )
{
  SIU.GPDO[LEDBASE+l].R = 0;
}

/**
 * @internal
 */
static inline void
  __led_off( unsigned l )
{
  SIU.GPDO[LEDBASE+l].R = 1;
}

/**
 * @internal
 */
static inline void
  __led_invert( unsigned l )
{
  SIU.GPDO[LEDBASE+l].R ^= 1;
}

#endif // __led_prv_h
