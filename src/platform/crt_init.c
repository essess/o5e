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

#include "platform/cstart.h"

/* --| TYPES    |--------------------------------------------------------- */

/**
 * Special symbol for copying sections from rom to ram. If size field is
 * zero, there are no more valid sections
 */
typedef struct __rom_copy_info
{
  char *       rom;    /* address in rom */
  char *       addr;   /* address in ram (executing address) */
  unsigned int size;   /* size of section */
} __rom_copy_info;

/**
 * Special symbol for initializing bss type sections. If size field is zero,
 * there are no more valid sections
 */
typedef struct __bss_init_info
{
  char *       addr;   /* address in ram  */
  unsigned int size;   /* size of section */
} __bss_init_info;

/* --| STATICS  |--------------------------------------------------------- */

static void
  rom_copy( void );

static void
  bss_zero( void );

/* --| INLINES  |--------------------------------------------------------- */

/**
 * @internal
 * @brief mwerks memset to avoid bringing in their entire runtime library
 *        for a simple initialization
 * @note ugly manual loop unrolling compliments of mwerks
 */
static inline void
  _fill_mem_( void * dst,
              int val,
              unsigned long n )
{

#define cps ((unsigned char *) src)
#define cpd ((unsigned char *) dst)
#define lps ((unsigned long *) src)
#define lpd ((unsigned long *) dst)
#define deref_auto_inc(p) *++(p)

  unsigned long     v = (unsigned char) val;
  unsigned long     i;

  dst = ((unsigned char *) dst) - 1;

  if (n >= 32)
  {
    i = (~ (unsigned long) dst) & 3;

    if (i)
    {
      n -= i;

      do
        deref_auto_inc(cpd) = (unsigned char)v;
      while (--i);
    }

    if (v)
      v |= v << 24 | v << 16 | v <<  8;

    dst = ((unsigned long *) (cpd + 1)) - 1;

    i = n >> 5;

    if (i)
      do
      {
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
        deref_auto_inc(lpd) = v;
      }
      while (--i);

    i = (n & 31) >> 2;

    if (i)
      do
        deref_auto_inc(lpd) = v;
      while (--i);

    dst = ((unsigned char *) (lpd + 1)) - 1;

    n &= 3;
  }

  if (n)
    do
      deref_auto_inc(cpd) = (unsigned char)v;
    while (--n);

}

/**
 * @internal
 * @brief mwerks memcpy implementation to avoid bringing in their entire
 *        runtime library for a simple initialization
 */
static inline void
  _memcpy_( void * dst,
            const void * src,
            unsigned int n )
{
  const char * p;
        char * q;

  if ((unsigned long) src < (unsigned long) dst)
  {
    for (p = (const char *) src + n, q = (char *) dst + n, n++; --n;)
      *--q = *--p;
  }
  else
  {
    for (p = (const char *) src - 1, q = (char *) dst - 1, n++; --n;)
      *++q = *++p;
  }
}

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

/* --| INTERNAL |--------------------------------------------------------- */

__declspec(section ".init")
static void
  rom_copy( void )
{
  extern __rom_copy_info _rom_copy_info[];     /*< linker defined */
  __rom_copy_info *dci = _rom_copy_info;

  while( !(dci->rom == 0 && dci->addr == 0 && dci->size == 0) )
  {
    if( dci->size && (dci->addr != dci->rom) )
        _memcpy_(dci->addr, dci->rom, dci->size);
    dci++;
  }
}

__declspec(section ".init")
static void
  bss_zero( void )
{
  extern __bss_init_info _bss_init_info[];     /*< linker defined */
  __bss_init_info *bii = _bss_init_info;

  while( !(bii->addr == 0 && bii->size == 0) )
  {
    if( bii->size )
        _fill_mem_(bii->addr, 0, bii->size);
    bii++;
  }
}
