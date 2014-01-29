/**
 * @file       err_get_code.c
 * @headerfile err.h
 * @author     sstasiak
 * @note       do not use traps in this api
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "trap.h"
#include "err.h"
#include "err/err_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/**
 * @public
 * @brief extract err code from err
 * @param[in] e err
 * @retval uint32_t code
 */
uint32_t
  err_get_code( err_t const *e )
{
  trap( e );
  return e->code;
}
