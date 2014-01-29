/**
 * @file   trap.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __trap_h
#define   __trap_h

#ifndef NDEBUG
  #define trap(exp_) \
    do { (void)sizeof(exp_); } while(0) \
    // traps are not recommended for this codebase \
    // do { if (!(exp_)) { asm("trap"); } } while(0)
#else
  #define trap(exp_) \
    do { (void)sizeof(exp_); } while(0)
#endif

#endif // __trap_h
