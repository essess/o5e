/**
 * @file   serial_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __serial_prv_h
#define   __serial_prv_h

#include "serial.h"

struct serial_t
{
  struct
  {
    uint8_t *ptr;
    unsigned size;
    unsigned cnt;
    unsigned idx;
  } buffer;
};

extern serial_t serial;

#endif // __serial_prv_h
