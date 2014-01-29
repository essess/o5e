/**
 * @file       serial_get.c
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

serial_t serial =
{
  .buffer =
  {
    .ptr  = 0,
    .size = 0,
    .cnt  = 0,
    .idx  = 0
  }
};

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief create/open a default serial port channel
 * @param[in] pbuff reference to caller supplied [in/out] buffer
 * @param[in] bytesize byte size of caller supplied buffer
 * @retval serial_t* reference to serial port context
 * @note { not threadsafe }
 */
serial_t *
  serial_get( uint8_t *pbuff,
              unsigned bytesize )
{
  err_assert( pbuff, CODE_SERIAL_SGPTR );
  err_assert( bytesize>=32, CODE_SERIAL_SGSIZE ); /**< arbitrary value */
  static serial_t *pserial = 0;
  if( !pserial )
  {
    pserial = &serial;
    pserial->buffer.ptr  = pbuff;
    pserial->buffer.size = bytesize;

    ESCI_A.CR1.B.SBR = 43;      /**< 115200 ~1% fast (116,280) */
    ESCI_A.CR1.B.ILT = 1;       /**< begin idle detect after stop bit detected */

    ESCI_A.CR1.B.TE = 1;        /**< enable tx buffer */
    ESCI_A.CR1.B.RE = 1;        /**< enable rx buffer */

    ESCI_A.CR2.B.ORIE = 1;      /**< enable error interrupts */
    ESCI_A.CR2.B.NFIE = 1;
    ESCI_A.CR2.B.FEIE = 1;
    ESCI_A.CR2.B.PFIE = 1;

    SIU.PCR[90].B.PA = 1;       /**< RX */
    SIU.PCR[89].B.PA = 1;       /**< TX */

    INTC.PSR[146].B.PRI = 1;    /**< unmask peripheral int */
  }
  return pserial;
}

/* --| INTERNAL |--------------------------------------------------------- */
