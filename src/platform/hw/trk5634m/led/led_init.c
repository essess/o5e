/**
 * @file       led_init.c
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

__declspec(section ".rodata")
static union
{
  uint16_t reg;
  struct
  {
    uint16_t    :3;       /*  */
    uint16_t  pa:3;       /*  */
    uint16_t obe:1;       /*  */
    uint16_t ibe:1;       /*  */
    uint16_t dsc:2;       /*  */
    uint16_t ode:1;       /*  */
    uint16_t hys:1;       /*  */
    uint16_t src:2;       /*  */
    uint16_t wpe:1;       /*  */
    uint16_t wps:1;       /*  */
  };
} const pcr = {
  .pa  = 0,
  .obe = 1,
  .ibe = 0,
  .dsc = 3,
  .ode = 1,
  .hys = 0,
  .src = 3,
  .wpe = 0,
  .wps = 0,
};

/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief init all leds to default state
 * @param none
 * @retval none
 */
void
  led_init( void )
{
  SIU.GPDO[LEDBASE+0].R = 1;
  SIU.GPDO[LEDBASE+1].R = 1;
  SIU.GPDO[LEDBASE+2].R = 1;
  SIU.GPDO[LEDBASE+3].R = 1;

  SIU.PCR[LEDBASE+0].R = pcr.reg;
  SIU.PCR[LEDBASE+1].R = pcr.reg;
  SIU.PCR[LEDBASE+2].R = pcr.reg;
  SIU.PCR[LEDBASE+3].R = pcr.reg;
}
