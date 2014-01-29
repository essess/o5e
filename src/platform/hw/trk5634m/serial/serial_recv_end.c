/**
 * @file       serial_recv_end.c
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
 * @brief release buffer from recv duty
 * @param[in] s serial port context
 * @retval none
 */
void
  serial_recv_end( serial_t *s )
{
  if( s == &serial )
    ESCI_A.CR1.B.RIE = 0;
  else
    err_push( CODE_SERIAL_SREPTR );
}

/* --| INTERNAL |--------------------------------------------------------- */
