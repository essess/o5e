/**
 * @file   flash.h
 * @author sean
 * @note   nothing in this api is threadsafe
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __flash_h
#define   __flash_h

#include <stdint.h>

typedef struct flash_t flash_t;                              /**< fwd decl */

/**
 * @public
 * @enum flash_err_t
 * @brief flash fcall return values
 */
typedef enum
{
  FLERR_OK = 0,
  FLERR_BUSY,
  FLERR_ALIGNMENT,
  FLERR_OPFAIL,
  FLERR_UNKNOWN
} flash_err_t;

/**
 * @public
 * @brief initialize flash (on first call) and returns the current context
 * @param none
 * @retval flash_t* reference to flash context
 */
flash_t *
  flash_get( void );

/**
 * @public
 * @brief swap to other flash storage block
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 * @note use @see{ flash_getblkptr } to get a raw ref to the new block
 */
flash_err_t
  flash_swap( flash_t *fptr );

/**
 * @public
 * @brief get raw reference to current flash block
 * @attention DO NOT deref while performing other operations upon flash
 * @param[in] fptr flash context
 * @retval uint8_t const* raw reference to the current flash block, 0 otherwise
 */
uint8_t const*
  flash_getblk_ptr( flash_t *fptr );

/**
 * @public
 * @brief get bytesize of current flash block
 * @param[in] fptr flash context
 * @retval unsigned size of flash block in bytes
 */
unsigned
  flash_getblk_bytesize( flash_t *fptr );

/**
 * @public
 * @brief unlock the current block and prepare for an erase operation
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_erase_begin( flash_t *fptr );

/**
 * @public
 * @brief start an erase operation on current block
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 * @note use @see { flash_busy_chk } to poll for when cycle is complete
 */
flash_err_t
  flash_erase( flash_t *fptr );

/**
 * @public
 * @brief lock all blocks and idle array
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_erase_end( flash_t *fptr );

/**
 * @public
 * @brief unlock the current block and prepare for a series of write
 *        operations
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_write_begin( flash_t *fptr );

/**
 * @public
 * @brief do doubleword write to designated offset of current block
 * @param[in] fptr flash context
 * @param[in] o offset into the current block, must be on modulo 8
 *              boundaries or FLERR_ALIGNMENT results
 * @param[in] dw reference to doubleword data
 * @retval flash_err_t FLERR_OK on success
 * @note use @see { flash_busy_chk } to poll for when cycle is complete
 */
flash_err_t
  flash_write( flash_t *fptr,
               uint32_t o,
               uint64_t *dw );

/**
 * @public
 * @brief lock all blocks and idle array
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_OK on success
 */
flash_err_t
  flash_write_end( flash_t *fptr );

/**
 * @public
 * @brief check if erase/write op on array is complete
 * @param[in] fptr flash context
 * @retval flash_err_t FLERR_BUSY while incomplete, FLERR_OK/FLERR_OPFAIL
 *                     upon completion, FLERR_UNKNOWN otherwise
 */
flash_err_t
  flash_busy_chk( flash_t *fptr );

#endif // __flash_h
