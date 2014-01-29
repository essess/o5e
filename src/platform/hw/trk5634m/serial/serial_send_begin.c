/**
 * @file       serial_send_begin.c
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
 * @brief claim buffer for xmit duty
 * @param[in] s serial port context
 * @param[in] bytecnt number of buffer bytes to send
 * @retval none
 */
void
  serial_send_begin( serial_t *s,
                     uint32_t bytecnt )
{
  if( s == &serial )
  {
    s->buffer.cnt = bytecnt;
    s->buffer.idx = 0;
    if( bytecnt )
    {
      err_assert( ESCI_A.CR1.B.TIE==0, CODE_SERIAL_SSBTIE );
      err_assert( ESCI_A.CR1.B.RIE==0, CODE_SERIAL_SSBRIE );
      ESCI_A.SR.B.TDRE = 1;
      ESCI_A.CR1.B.TIE = 1;
      ESCI_A.DR.B.D = s->buffer.ptr[s->buffer.idx++];
    }
  }
  else
    err_push( CODE_SERIAL_SSBPTR );
}

/* --| INTERNAL |--------------------------------------------------------- */
