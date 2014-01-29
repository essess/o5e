/**
 * @file       cal_getblk_ptr.c
 * @headerfile cal.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/cal/cal_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief get a reference to the volatile calibration block
 * @param none
 * @retval uint8_t* reference
 */
uint8_t *
  cal_getblk_ptr( void )
{
  return data_ptr( cal_ptr() );
}

/* --| INTERNAL |--------------------------------------------------------- */