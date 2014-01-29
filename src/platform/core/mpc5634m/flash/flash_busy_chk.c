/**
 * @file       flash_busy_chk.c
 * @headerfile flash.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "flash.h"
#include "platform/core/mpc5634m/flash/flash_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief check if erase/write op on array is complete
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_BUSY while incomplete, FLERR_OK/FLERR_OPFAIL
 *                     upon completion, FLERR_UNKNOWN otherwise
 */
flash_err_t
  flash_busy_chk( flash_t *fptr )
{
  flash_err_t e = FLERR_UNKNOWN;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_BUSY) )
  {
    if( !CFLASH0.MCR.B.DONE )
      return FLERR_BUSY;
    fptr->state = FLSTATE_READY;
    CFLASH0.MCR.B.EHV = 0;
    e = CFLASH0.MCR.B.PEG ? FLERR_OK : FLERR_OPFAIL;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
