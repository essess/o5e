/**
 * @file       tpu_cis1.c
 * @headerfile task_engpos_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief tpu channel interupt 1 status handler (cam)
 * @param none
 * @retval none
 */
void
  vector69( void )
{

  /* according to fs docs, we're here because a change in engpos status occured
     the plan is: figure out what happened and post to the engpos thread */

  if( ETPU.CHAN[1].SCR.B.CIOS )
  {
    err_push( CODE_ENGPOS_CIS1MI );
    ETPU.CHAN[1].SCR.B.CIOS = 1;  /**< clr overflow */
  }

  ETPU.CHAN[1].SCR.B.CIS = 1;     /**< clr int */
}