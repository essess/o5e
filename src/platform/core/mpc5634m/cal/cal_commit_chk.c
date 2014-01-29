/**
 * @file       cal_commit_chk.c
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
#include "util.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

/**
 * @internal
 * @brief invalidate the cal stored in the current flash blk
 * @note blocking call
 * @param[in] pflash flash context
 * @retval int 0 on failure
 */
static int
  invalidate( flash_t *pflash )
{
  resv_overlay_t resv = { .is_valid = 0 };
  if( flash_write_begin(pflash) == FLERR_OK )
  {
    /* dword[1] is the 'is_valid' flag */
    if( flash_write( pflash, resv_offset()+sizeof(uint64_t), &resv.uint64[1] ) == FLERR_OK )
    {
      while( flash_busy_chk(pflash) == FLERR_BUSY ) {};
      if( flash_write_end(pflash) == FLERR_OK )
        return ~0;
    }
  }
  return 0;
}

/**
 * @internal
 * @brief store the current cal's flash crc in the current flash blk
 * @note blocking call
 * @param[in] pflash flash context
 * @param[in] crc crc32 value
 * @retval int 0 on failure
 */
static int
  write_crc( flash_t *pflash,
             uint32_t crc )
{
  resv_overlay_t resv = { .uint64[0] = ~0 };
  resv.crc = crc;

  if( flash_write_begin(pflash) == FLERR_OK )
  {
    /**< dword[0] is crc */
    if( flash_write( pflash, resv_offset(), &resv.uint64[0] ) == FLERR_OK )
    {
      while( flash_busy_chk(pflash) == FLERR_BUSY ) {};
      if( flash_write_end(pflash) == FLERR_OK )
        return ~0;
    }
  }
  return 0;
}

/**
 * @internal
 * @brief write substate state machine sequencing
 * @param[in] pflash flash context
 * @retval ccs_t indicate new state to parent, specifically, the transition
 *               from WRITE -> IDLE when complete (or ERROR)
 */
static ccs_t
  write( flash_t *pflash )
{
  /* idle->write->busy->write->busy-> ...                  */
  /*  ... ->crc_flash->crc_cal->invalidate->validate->idle */
  enum { IDLE, WRITE, BUSY, CRC_FLASH, CRC_CAL, INVALIDATE, VALIDATE };
  static int ws = IDLE;

  static uint64_t *p;
  static unsigned offset;
  static unsigned bytesize;

  static uint32_t crc;

  switch( ws )
  {
    case IDLE:
      if( flash_write_begin(pflash) == FLERR_OK )
      {
        p = (uint64_t*)data_ptr(cal_ptr());
        offset = 0;
        bytesize = data_bytesize();
        ws = WRITE;
      }
      else
      {
        err_push( CODE_CAL_CCCEFWB );
        return CCS_ERROR;
      }
      break;
    case WRITE:
      if( offset < bytesize )
      {
        if( flash_write(pflash, offset, p) == FLERR_OK )
        {
          p++;
          offset += sizeof(*p);
          ws = BUSY;
        }
        else
        {
          err_push( CODE_CAL_CCCEFW );
          return CCS_ERROR;
        }
      }
      else
      {
        if( flash_write_end(pflash) == FLERR_OK )
          ws = CRC_FLASH;
        else
        {
          err_push( CODE_CAL_CCCEFWE );
          return CCS_ERROR;
        }
      }
      break;
    case BUSY:
      if( flash_busy_chk(pflash) != FLERR_BUSY )
        ws = WRITE;
      break;
    case CRC_FLASH:
      crc = crc32( 0, data_ptr((uint8_t*)flash_getblk_ptr(pflash)), data_bytesize() );
      ws = CRC_CAL;
      break;
    case CRC_CAL:
      /* this is how we know that the write was performed correctly */
      if( crc == crc32(0, data_ptr(cal_ptr()), data_bytesize()) )
        ws = INVALIDATE;
      else
      {
        err_push( CODE_CAL_CCCECRCCHK );
        return CCS_ERROR;
      }
      break;
    case INVALIDATE:
      if( (flash_swap( pflash ) == FLERR_OK) &&
          (invalidate( pflash )) )
        ws = VALIDATE;
      else
      {
        err_push( CODE_CAL_CCCEINVALIDATE );
        return CCS_ERROR;
      }
      break;
    case VALIDATE:
      if( (flash_swap( pflash ) == FLERR_OK) &&
          (write_crc( pflash, crc )) )
      {
        ws = IDLE; /* done */
        return CCS_IDLE;
      }
      err_push( CODE_CAL_CCCEVALIDATE );
      return CCS_ERROR;
      break;
    default:
      err_push( CODE_CAL_CCCEBADWS );
      return CCS_ERROR;
      break;
  }
  return CCS_WRITE;
}

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief poll commit operation started by @see { cal_commit }
 * @param none
 * @retval ccs_t current state of operation, CCS_IDLE when complete
 */
ccs_t
  cal_commit_chk( void )
{
  switch( cal.state )
  {
    case CCS_ERASE:
      /* still busy?: */
      if( flash_busy_chk(cal.pflash) != FLERR_BUSY )
      {
        if( flash_erase_end(cal.pflash) != FLERR_OK )
        {
          err_push( CODE_CAL_CCCFEE );
          cal.state = CCS_ERROR;
        }
        else
          cal.state = CCS_WRITE;  /**< go copy vol cal to new clean block */
      }
      break;
    case CCS_WRITE:
      cal.state = write( cal.pflash );
      break;
  }
  return cal.state;
}

/* --| INTERNAL |--------------------------------------------------------- */
