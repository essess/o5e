/**
 * @file   cstart.h
 * @author sean
 * @internal
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __cstart_h
#define   __cstart_h

/**
 * @public
 * @brief o5e c application hard reset entry point
 * @param[in] none
 * @param[out] none
 * @retval none
 */
void
  cstart( void );

/**
 * @public
 * @brief Startup hook called first thing out of reset. Use this to get
 *        any core specific functionality turned on/off/reset asap
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * do not: use sram from your handler
 * do not: touch any platform specific i/o, use hw_init() to do that
 * you can: use any register for temp storage freely
 * try to: make your way through as fast as possible
 * try to: use asm - the crt is not available for you
 */
void
  core_init( void );

/**
 * @public
 * @brief Startup hook called first thing out of reset following core_init().
 *        Use this to get any hardware specific functionality turned
 *        on/off/reset asap
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * you can: use any register for temp storage freely
 * you can: use sram freely
 * try to: make your way through as fast as possible
 * try to: use asm - the crt is not available for you
 */
void
  hw_init( void );

/**
 * @public
 * @brief initialize c runtime
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * try to: use asm - the crt is not available for you
 */
void
  crt_init( void );

/**
 * @public
 * @brief Final opportunity to initalize hardware specific items before
 *        dropping into main()
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * you can: depend on the crt being 'up'
 */
void
  hw_init_final( void );

/**
 * @public
 * @brief Final opportunity to initalize core specific items before dropping
 *        into main()
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * you can: depend on the crt being 'up'
 */
void
  core_init_final( void );

#endif // __cstart_h
