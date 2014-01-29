/**
 * @file   ana_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __ana_prv_h
#define   __ana_prv_h

#include "ana.h"

/* cfifo header helpers: */
#define EOQ                 (1u<<31)
#define PAUSE               (1u<<30)
#define REPEAT              (1u<<29)
#define EB(x_)              ((x_&1u)<<26)
#define BN(x_)              ((x_&1u)<<25)

/**
 * @internal
 * @brief sample buffer which dma dumps into directly
 */
extern vuint16_t samples[];

/**
 * @internal
 * @brief predefined command queue
 */
extern uint32_t cmd_queue[];

/**
 * @internal
 * @brief dma error handler
 */
void
  ana_errhnd( unsigned );

/**
 * @internal
 * @brief internal ana context
 */
typedef struct ana_t
{
  ana_evt_cb_t *pcb;
} ana_t;

extern ana_t ana;

#endif // __ana_prv_h
