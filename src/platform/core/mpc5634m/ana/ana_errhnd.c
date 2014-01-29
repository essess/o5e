/**
 * @file       ana_errhnd.c
 * @headerfile ana_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/ana/ana_prv.h"
#include "platform/core/mpc5634m/core_prv.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief dma error handler
 */
void
  ana_errhnd( unsigned esr )
{
  union
  {
     uint32_t reg;
     struct
     {
     uint32_t VLD:1;        /* Logical OR of all DMAERRH */
     uint32_t    :14;       /* Reserved */
     uint32_t ECX:1;        /* (new in MPC563xM) */
     uint32_t GPE:1;        /* Group Priority Error */
     uint32_t CPE:1;        /* Channel Priority Error  */
     uint32_t ERRCHN:6;     /* ERRCHN[5:0] ch# of the last recorded error */
     uint32_t SAE:1;        /* Source Address Error 0  */
     uint32_t SOE:1;        /* Source Offset Error */
     uint32_t DAE:1;        /* Destination Address Error */
     uint32_t DOE:1;        /* Destination Offset Error */
     uint32_t NCE:1;        /* Nbytes/Citer Configuration Error */
     uint32_t SGE:1;        /* Scatter/Gather Configuration Error */
     uint32_t SBE:1;        /* Source Bus Error */
     uint32_t DBE:1;        /* Destination Bus Error  */
     };
  } err = { .reg = esr };

  ana_evt_t evt = AE_UNK;
  switch( err.ERRCHN )
  {
    case 10: evt = AE_ERRCFIFO; break;
    case 11: evt = AE_ERRRFIFO; break;
    default:
      err_push( CODE_ANA_UNKERR );
      return;
  }
  ana.pcb( evt );
}
