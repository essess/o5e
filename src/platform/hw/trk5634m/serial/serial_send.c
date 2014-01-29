/**
 * @file       serial_send.c
 * @headerfile serial.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/hw/trk5634m/serial/serial_prv.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief poll transmitter stats
 * @param[in] s serial port context
 * @retval int !0 while transmit in progress
 */
int
  serial_send( serial_t *s )
{
  if( s == &serial )
    return (s->buffer.idx < s->buffer.cnt);
  err_push( CODE_SERIAL_SSPTR );
  return 0;
}

/* --| INTERNAL |--------------------------------------------------------- */
