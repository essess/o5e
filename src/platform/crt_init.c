/**
 * @file       crt_init.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include <__mem.h>
#include "platform/cstart.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */
__declspec(section ".init")
static void
  rom_copy( void )
{
  /**
   * Special symbol for copying sections from rom to ram. If size field is
   * zero, there are no more valid sections
   */
  typedef struct __rom_copy_info
  {
    char *rom;        /* address in rom */
    char *addr;       /* address in ram (executing address) */
    unsigned size;    /* size of section */
  } __rom_copy_info;

  extern __rom_copy_info _rom_copy_info[];     /*< linker defined */
  __rom_copy_info *dci = _rom_copy_info;

  while( !(dci->rom == 0 && dci->addr == 0 && dci->size == 0) )
  {
    if( dci->size && (dci->addr != dci->rom) )
        memcpy(dci->addr, dci->rom, dci->size);
    dci++;
  }
}

/* --| INTERNAL |--------------------------------------------------------- */
__declspec(section ".init")
static void
  bss_zero( void )
{
  /**
   * Special symbol for initializing bss type sections. If size field is zero,
   * there are no more valid sections
   */
  typedef struct __bss_init_info
  {
    char *addr;       /* address in ram  */
    unsigned size;    /* size of section */
  } __bss_init_info;

  extern __bss_init_info _bss_init_info[];     /*< linker defined */
  __bss_init_info *bii = _bss_init_info;

  while( !(bii->addr == 0 && bii->size == 0) )
  {
    if( bii->size )
        __fill_mem(bii->addr, 0, bii->size);
    bii++;
  }
}

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

/**
 * @public
 * @brief initialize c runtime
 * @param[in] none
 * @param[out] none
 * @retval none
 *
 * try to: use asm - the crt is not available for you
 */
__declspec( vle_off )
__declspec( section ".init" )
asm void
  crt_init( void )
{
        extern void * volatile _SDA_BASE_;   /**< linker generated         */
        extern void * volatile _SDA2_BASE_;  /**< linker generated         */
        nofralloc

        stwu    rsp, -8(rsp)             /**< setup a junk eabi record     */
        xor     r2, r2, r2               /*                                */
        stw     r2, 0(rsp)               /**< .. and terminate             */
        lis     r2, _SDA2_BASE_@ha       /**< .sdata2 - initialized const  */
        addi    r2, r2, _SDA2_BASE_@l    /*             small global data  */
        lis     r13, _SDA_BASE_@ha       /**< .sdata - initialized small   */
        addi    r13, r13, _SDA_BASE_@l   /*            global data         */
        mflr    r31
        bl      rom_copy                 /**< run the rest as pure C since */
        bl      bss_zero                 /*   base regs are setup          */
        mtlr    r31
        blr
}
