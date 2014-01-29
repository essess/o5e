/**
 * @file       task_err.c
 * @headerfile task_err.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "cocoos.h"
#include "task/task_err.h"
#include "task/err/task_err_prv.h"
#include "led.h"
#include "err.h"

/* all of the following assume a 1KHz tick rate */
#define BIT_SHORT     (200)         /**< 0 bit  */
#define BIT_LONG      (700)         /**< 1 bit  */
#define BIT_PAUSE     (900)

#define CHIRP         (40)
#define CHIRP_CYCLES  (20)
#define CHIRP_DWELL   (1500)

#define DWELL         (1000)

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief monitor error codes and displays if present
 */
void
  task_err( void )
{
  task_open();
  static unsigned i;
  static uint32_t code;

  /* code display breakdown:                                                 */
  /*       [chirp] CHIRP_DWELL [bits] DWELL (repeat if code still exists)    */
  /* [chirp]: (on)CHIRP, (off)CHIRP, (on)CHIRP, ... , (off)CHIRP             */
  /*  [bits]: [bit], (off)BIT_PAUSE, [bit], ... , (off)BIT_PAUSE             */
  /*                                                                         */
  /* bits are sent out msb first; left to right as laid out from code text:  */
  /* 0x010f goes out as 1,0,f (the last 12b are all that counts):            */
  /* pattern: CHIRP sssl.ssss.llll                                           */
  /*                0001.0000.1111                                           */
  /*               |   1|   0|   f|                                          */
  /*                                                                         */
  /* the above breaks down as:                                               */
  /*                000100.001111                                            */
  /*                     |      +-- error  (0 to 63) = 15                    */
  /*                     +----------module (0 to 63) = 4                     */

  while(1)
  {
    code = err_peek();
    if( code != CODE_NONE )
    {
      /* CHIRP  */
      i = CHIRP_CYCLES;
      while( i )
      {
        led_on( LED_ERR );
        task_wait( CHIRP );
        led_off( LED_ERR );
        task_wait( CHIRP );
        i--;
      }
      task_wait( CHIRP_DWELL );
      /* [bits] */
      for(i=11 ; i <= 11 ; i--)   /**< codes are 16b wide [15:0], but only */
      {                           /*   the last 12b really count to a user */
        led_on( LED_ERR );        /*   or support provider                 */
        task_wait( (code&(1ul<<i))?BIT_LONG:BIT_SHORT );
        led_off( LED_ERR );
        task_wait( BIT_PAUSE );
      }
      task_wait( DWELL );
    }
    else
      task_wait( 500 );
  }
  task_close();
}
