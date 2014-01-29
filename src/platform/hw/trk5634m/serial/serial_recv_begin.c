/**
 * @file       serial_recv_begin.c
 * @headerfile serial.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/hw/trk5634m/serial/serial_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief claim buffer for recv duty
 * @param[in] s serial port context
 * @retval <type> <desc>
 */
void
  serial_recv_begin( serial_t *s )
{
  if( s == &serial )
  {
    err_assert( ESCI_A.CR1.B.TIE==0, CODE_SERIAL_SRBTIE );
    err_assert( ESCI_A.CR1.B.RIE==0, CODE_SERIAL_SRBRIE );
    s->buffer.idx = 0;
    s->buffer.cnt = 0;
    ESCI_A.SR.B.RDRF = 1;
    ESCI_A.CR1.B.RIE = 1;
  }
  else
    err_push( CODE_SERIAL_SRBPTR );
}

/* --| INTERNAL |--------------------------------------------------------- */
