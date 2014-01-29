/**
 * @file       cal_prv.c
 * @headerfile cal_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/cal/cal_prv.h"
#include "util.h"
#include "err.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

/**
 * @internal
 * @brief if flash block is valid, load to volatile calibration space, swap
 *        to alternate block otherwise.
 * @param[in] pflash flash context
 * @retval int 0 if cal invalid
 */
static int
  cal_try_load( flash_t *pflash )
{
  uint8_t const *pfblk = flash_getblk_ptr( pflash );
  resv_overlay_t const *const presv = (resv_overlay_t*)resv_ptr((uint8_t*)pfblk);
  if( presv->is_valid )
  {
    /* check crc before completely trusting this block: */
    uint32_t const crc = crc32( 0, data_ptr((uint8_t*)pfblk), data_bytesize() );
    if( presv->crc == crc )
    {
      wordcpy( (uint32_t*)data_ptr(cal_ptr()), (uint32_t*)pfblk, data_bytesize() );
      return ~0;  /**< good cal, and it's loaded now */
    }
  }
  /* no good, go ahead and swap blocks in prep for next try: */
  if( flash_swap(pflash) != FLERR_OK )
    err_push( CODE_CAL_CTLSWAP );
  return 0;
}

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @public
 * @brief get absolute start address of entire volatile calibration block
 * @param none
 * @retval uint8_t* calibration block reference
 */
asm uint8_t *
  cal_ptr( void )
{
  extern unsigned long _cal_ram_start;    /**< linker defined */
  nofralloc
  lis   r3, _cal_ram_start@ha
  addi  r3, r3, _cal_ram_start@l
  tweqi r3, 0
  blr
}

/**
 * @public
 * @brief get byte size of entire volatile calibration block
 * @param none
 * @retval unsigned size of volatile calibration block in bytes
 */
asm unsigned
  cal_bytesize( void )
{
  extern unsigned long _cal_ram_bytesize; /**< linker defined */
  nofralloc
  lis   r3, _cal_ram_bytesize@ha
  addi  r3, r3, _cal_ram_bytesize@l
  tweqi r3, 0
  blr
}

/**
 * @internal
 * @brief find first valid cal in flash and load to volatile calibration space
 * @param[in] pflash flash context
 * @retval int 0 if flash contains no valid data, in that case, volatile cal
 *             space will be initialized w/0xff's
 */
int
  cal_load( flash_t *pflash )
{
  /* ensure volatile cal space is large enough to contain what's in flash: */
  if( cal_bytesize() >= flash_getblk_bytesize(pflash) )
  {
    if( cal_try_load(pflash) || cal_try_load(pflash) )
      return ~0;
  }
  else
    err_push( CODE_CAL_CLTOOSMALL );
  /* nothing found or err, wipe volatile cal space to be safe */
  wordfill( (uint32_t*)cal_ptr(), 0, cal_bytesize() );
  return 0;
}
