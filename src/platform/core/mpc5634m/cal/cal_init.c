/**
 * @file       cal_init.c
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

cal_t cal =
{
  .pflash = 0,
  .state = CCS_IDLE
};

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief load volatile cal blocks from their backing store
 * @retval int 0 on failure
 * @note { not threadsafe }
 */
int
  cal_init( void )
{
  static int loaded = 0;
  /**
   * Only ONE attempt to load the cal from its backing store is performed
   * during the program's lifetime. This is to prevent someone from fixing
   * the cal backing store and then assume that everything is okay. You must
   * go through a proper reboot (a hard reset) after committing a new/initial
   * cal into the backing store
   */
  if( !cal.pflash )
  {
    cal.pflash = flash_get();
    if( cal.pflash )
      loaded = cal_load( cal.pflash );
    else
      err_push( CODE_CAL_CIFPTR );
  }
  return loaded;
}

/* --| INTERNAL |--------------------------------------------------------- */
