/**
 * @file   serial.h
 * @author sstasiak
 *
 * @brief Rudimentry polled half-duplex style serial communications api. A
 *        single (caller supplied) buffer is utilized which is locked from
 *        it's complementry operation by the use of _begin/_end
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __serial_h
#define   __serial_h

#include <stdint.h>

typedef struct serial_t serial_t; /**< fwd decl */

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
              unsigned bytesize );

/**
 * @public
 * @brief claim buffer for recv duty
 * @param[in] s serial port context
 * @retval <type> <desc>
 */
void
  serial_recv_begin( serial_t *s );

/**
 * @public
 * @brief poll receiver stats
 * @param[in] s serial port context
 * @retval unsigned number of bytes received since last poll
 */
unsigned
  serial_recv( serial_t *s );

/**
 * @public
 * @brief release buffer from recv duty
 * @param[in] s serial port context
 * @retval none
 */
void
  serial_recv_end( serial_t *s );

/**
 * @public
 * @brief claim buffer for xmit duty
 * @param[in] s serial port context
 * @param[in] bytecnt number of buffer bytes to send
 * @retval none
 */
void
  serial_send_begin( serial_t *s,
                     uint32_t bytecnt );

/**
 * @public
 * @brief poll transmitter stats
 * @param[in] s serial port context
 * @retval int !0 while transmit in progress
 */
int
  serial_send( serial_t *s );

/**
 * @public
 * @brief release buffer from xmit duty
 * @param[in] s serial port context
 * @retval none
 */
void
  serial_send_end( serial_t *s );

#endif // __serial_h
