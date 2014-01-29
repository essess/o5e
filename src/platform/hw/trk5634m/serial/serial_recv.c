/**
 * @file       serial_recv.c
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
 * @brief poll receiver stats
 * @param[in] s serial port context
 * @retval unsigned number of bytes received since last poll
 */
unsigned
  serial_recv( serial_t *s )
{
  if( s == &serial )
    return s->buffer.idx;
  err_push( CODE_SERIAL_SRPTR );
  return 0;
}

/* --| INTERNAL |--------------------------------------------------------- */
