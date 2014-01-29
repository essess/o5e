/**
 * @file   err_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __err_prv_h
#define   __err_prv_h

#include "lifo.h"
#include "fifo.h"

struct err_t
{
  fifo_t;
  uint32_t code;
  uint64_t ts;
};

extern err_t err_pool[ERR_DEPTH];
extern err_t *err_free_root;              /**< pool of free err_t blocks   */
extern fifo_t err_fifo_root;              /**< code fifo stack             */
extern err_cb_t *notify;

#endif // __err_prv_h
