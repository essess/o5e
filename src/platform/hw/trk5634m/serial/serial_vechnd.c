/**
 * @file       serial_vechnd.c
 * @headerfile serial_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/hw/trk5634m/serial/serial_prv.h"
#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief static SCIA combined interrupt handler
 */
void
  vector146( void ) __attribute__((used))
{
  if( ESCI_A.SR.B.TDRE && (serial.buffer.idx<serial.buffer.cnt) )
    ESCI_A.DR.B.D = serial.buffer.ptr[serial.buffer.idx++];
  if( ESCI_A.SR.B.RDRF )
  {
    uint8_t const d = ESCI_A.DR.B.D;  /**< pull unconditionally */
    if( serial.buffer.idx < serial.buffer.size )
      serial.buffer.ptr[serial.buffer.idx++] = d;
    else
      err_push( CODE_SERIAL_SVRXFULL ); /**< drop */
  }
  if( ESCI_A.SR.B.OR )
    err_push( CODE_SERIAL_SVOVERRUN );
  if( ESCI_A.SR.B.NF )
    err_push( CODE_SERIAL_SVNOISE );
  if( ESCI_A.SR.B.FE )
    err_push( CODE_SERIAL_SVFRAMING );
  if( ESCI_A.SR.B.PF )
    err_push( CODE_SERIAL_SVPARITY );
  ESCI_A.SR.R = ESCI_A.SR.R;   /**< clr int sources */
}
