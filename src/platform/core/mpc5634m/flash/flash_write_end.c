/**
 * @file       flash_write_end.c
 * @headerfile flash.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/flash/flash_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief lock all blocks and idle array
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_write_end( flash_t *fptr )
{
  flash_err_t e = FLERR_BUSY;
  if( (fptr ==  &f) && (fptr->state == FLSTATE_READY) )
  {
    fptr->state = FLSTATE_IDLE;
    CFLASH0.MCR.B.PGM = 0;
    CFLASH0.LMLR.R |= 0xff;  /**< set to lock ALL blocks */
    CFLASH0.SLMLR.R |= 0xff;
    e = FLERR_OK;
  }
  return e;
}

/* --| INTERNAL |--------------------------------------------------------- */
