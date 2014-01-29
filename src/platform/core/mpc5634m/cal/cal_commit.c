/**
 * @file       cal_commit.c
 * @headerfile cal.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/cal/cal_prv.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief begin operation which commits the volatile cal block back to
 *        storage
 * @attention DO NOT MODIFY the cal block while a commit operation is
 *            in progress
 * @param none
 * @retval ccs_t current state of operation
 */
ccs_t
  cal_commit( void )
{
  /* always start from the idle state. if you're uncertain which state */
  /* cal is in, feel free to call @see { cal_commit_chk } first:       */
  if( cal.state == CCS_IDLE )
  {
    /* swap to other page and begin erase on it: */
    if( flash_swap(cal.pflash) == FLERR_OK )
    {
      if( flash_erase_begin(cal.pflash) == FLERR_OK )
      {
        if( flash_erase(cal.pflash) == FLERR_OK )
          cal.state = CCS_ERASE;
        else
        {
          err_push( CODE_CAL_CCE );
          cal.state = CCS_ERROR;
        }
      }
      else
      {
        err_push( CODE_CAL_CCEB );
        cal.state = CCS_ERROR;
      }
    }
    else
    {
      err_push( CODE_CAL_CCSWAP );
      cal.state = CCS_ERROR;
    }
  }
  return cal.state;
}

/* --| INTERNAL |--------------------------------------------------------- */
