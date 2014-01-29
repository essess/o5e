/**
 * @file       edma_init.c
 * @headerfile core_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @internal
 * @brief setup default groupings and priorities
 * @param none
 * @retval none
 */
void
  edma_init( void )
{
  /* group:   round-robin */
  /* channel: fixed-pri   */
  EDMA.CR.B.EDBG = 1;
  EDMA.CR.B.ERGA = 1;
  EDMA.CR.B.EBW  = 1;
  INTC.PSR[10].B.PRI = 2; /**< unmask dma irq src */
  /* default fixed pri's out of reset are good for now */
}

/* --| INTERNAL |--------------------------------------------------------- */