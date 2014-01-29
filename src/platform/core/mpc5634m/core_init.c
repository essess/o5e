/**
 * @file       core_init.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/cstart.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

/**
 * @internal
 * @brief perform word write from ram
 * void set( uint32_t value, uint32_t addr, uint32_t off )
 */
__declspec( section ".rodata" )
static unsigned const set[] =
{
  0x7c64292e,   /**< stwx r3, r4, r5 */
  0x7c0004ac,   /**< msync           */
  0x4c00012c,   /**< isync           */
  0x4e800020    /**< blr             */
};

__declspec( vle_off )
__declspec( section ".init" )
static asm void
  flash_cfg( void )
{

  extern unsigned _internal_ram_end;  /**< linker provided            */
  enum { BIUCR = 0xC3F8801Cul };
  enum { BIUCR_VAL  = 0x00006B00ul,   /**< all prefetching bank1 ONLY */
         BIUAPR_VAL = 0xffffffc7ul }; /**< no dma access to flash     */
  nofralloc
  mflr    r30                       /**< no stack!                   */

  lis     r5, set@h                 /**< src                         */
  ori     r5, r5, set@l
  lis     r6, _internal_ram_end@h   /**< dest                        */
  ori     r6, r6, (_internal_ram_end-sizeof(set))@l
  lwz     r4, 0(r5)           /**< unrolled brute force copy:        */
  stw     r4, 0(r6)
  lwz     r4, 4(r5)
  stw     r4, 4(r6)
  lwz     r4, 8(r5)
  stw     r4, 8(r6)
  lwz     r4, 12(r5)
  stw     r4, 12(r6)
  lis     r4, BIUCR@h         /**< BIUCR (base)                      */
  ori     r4, r4, BIUCR@l
  lis     r3, BIUCR_VAL@h
  ori     r3, r3, BIUCR_VAL@l
  xor     r5, r5, r5          /**< BIUCR+0=BIUCR                     */
  mtlr    r6                  /**< addr of set()                     */
  blrl
  lis     r3, BIUAPR_VAL@h
  ori     r3, r3, BIUAPR_VAL@l
  li      r5, 4               /**< BIUCR+4=BIUAPR                    */
  mtlr    r6                  /**< addr of set()                     */
  blrl

  mtlr  r30
  blr
}

__declspec( vle_off )
__declspec( section ".init" )
static asm void
  fmpll_cfg( void )
{
        nofralloc

        /* MHz :    80 70 60 50 40 30 20 10   */
        /* ESYNCR1: 40 35 60 50 40 60 40 1,40 */
        /* ESYNCR2: 1  1  2  2  2  3  3  3    */

        lis     r3, 0xC3F8          /**< loadup PLL region base            */
        lis     r4, 0xF000          /**< EPREDIV -> 0-1 to 1110-15         */
        ori     r4, r4, 40          /**< EMFD -> 32 to 96                  */
        stw     r4, 8(r3)           /**< write ESYNCR1                     */
        li      r4, 1               /**< ERFD -> 0-2,4,8 and 11-16         */
        stw     r4, 12(r3)          /**< write ESYNCR2                     */
@loop:  lwz     r4, 4(r3)           /**< check SYNSR, wait lock            */
        andi.   r4, r4, (1<<3)      /**< is LOCK set? ...                  */
        beq     @loop               /**< ... wait till set                 */
        blr
}

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

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
__declspec( vle_off )
__declspec( section ".init" )
asm void
  core_init( void )
{
        extern void * volatile _stack_addr; /**< linker generated          */
        nofralloc
        mflr    r31                   /**< no stack!                       */

        li      r1, (1<<0) | (1<<9)   /**< enable and flush BTB: static    */
        mtbucsr r1                    /*   branch prediction is ignored    */
        isync                         /*   from this point on              */
        bl      fmpll_cfg
        bl      flash_cfg
        li      r1, 752               /**< 94k/4 bytes/32 GPRs = 752       */
        mtctr   r1
        lis     r1, 0x40000000@h      /**< sram starts at 0x40000000       */
@next:  stmw    r0, 0(r1)             /**< all 32 gprs                     */
        addi    r1, r1, 32*4          /*   32 GPRs * 4 bytes = 128         */
        bdnz    @next
        msync
        /* NOTE: as a byproduct of the above, we're already
         *       at _stack_addr
         */
        lis     rsp, _stack_addr@ha   /**< loadup initial sp               */
        addi    rsp, rsp, _stack_addr@l

        mtlr    r31
        blr
}

/* --| INTERNAL |--------------------------------------------------------- */
