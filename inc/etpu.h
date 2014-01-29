/**
 * @file   etpu.h
 * @author sstasiak
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __etpu_h
#define   __etpu_h

/**
 * @public
 * @brief initialize etpu, start timebase with @see { core_start_timers }
 */
void
  etpu_init( void );

/**
 * @public
 * @brief returns tcr1 timebase freq
 */
unsigned
  etpu_tcr1_freq( void );

#endif // __etpu_h
