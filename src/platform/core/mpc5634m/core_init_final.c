/**
 * @file       core_init_final.c
 * @headerfile cstart.h
 * @author     sean
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/cstart.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "core.h"
#include "platform/core/mpc5634m/core_prv.h"

enum
{
  SPE_ON  = (1<<25),
  SPE_OFF = (0<<25)
};

enum
{
  EE_MASKED   = (0<<15),
  EE_UNMASKED = (1<<15)
};

enum
{
  CE_MASKED   = (0<<17),
  CE_UNMASKED = (1<<17)
};

enum
{
  ME_MASKED   = (0<<12),
  ME_UNMASKED = (1<<12)
};

#ifdef __SPE__
#define SPE   SPE_ON
#else
#define SPE   SPE_OFF
#endif

#define EE  EE_UNMASKED
#define CE  CE_UNMASKED
#define ME  ME_UNMASKED

#define INITIAL_MSR   ( SPE | EE | CE | ME )

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */

__declspec( section ".init" )
static asm void
  decr_1khz( void )
{
  enum { RATE = ((80000000/1000)-1) }; /**< 1000Hz at 80MHz                */
  fralloc

  xor     r0, r0, r0
  mttbu   r0
  mttbl   r0                           /**< wipe timebase                  */
  lis     r0, RATE@h
  ori     r0, r0, RATE@l
  mtdecar r0
  mtdec   r0                           /**< reload = initial               */
  mftcr   r0
  lis     r3, 0x0440                   /**< TCR[DIE] | TCR[ARE]            */
  or      r0, r0, r3
  mttcr   r0

  frfree
  blr
}

/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */

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
__declspec( section ".init" )
void
  core_init_final( void )
{
  register int r;

  asm
  {
    lis      r, _f_handlers@h
    ori      r, r, _f_handlers@l
    mtivpr   r

    li       r, ivor0_handler@l
    mtivor0  r   /**< Critical input (SPR 400)                         */
    li       r, ivor1_handler@l
    mtivor1  r   /**< Machine check interrupt (SPR 401)                */
    li       r, ivor2_handler@l
    mtivor2  r   /**< Data storage interrupt (SPR 402)                 */
    li       r, ivor3_handler@l
    mtivor3  r   /**< Instruction storage interrupt (SPR 403)          */
    li       r, ivor4_handler@l
    mtivor4  r   /**< External input interrupt (SPR 404)               */
    li       r, ivor5_handler@l
    mtivor5  r   /**< Alignment interrupt (SPR 405)                    */
    li       r, ivor6_handler@l
    mtivor6  r   /**< Program interrupt (SPR 406)                      */
    li       r, ivor7_handler@l
    mtivor7  r   /**< Floating-point unavailable interrupt (SPR 407)   */
    li       r, ivor8_handler@l
    mtivor8  r   /**< System call interrupt (SPR 408)                  */
    li       r, ivor9_handler@l
    mtivor9  r   /**< Auxiliary processor (SPR 409)                    */
    li       r, ivor10_handler@l
    mtivor10 r   /**< Decrementer interrupt (SPR 410)                  */
    li       r, ivor11_handler@l
    mtivor11 r   /**< Fixed-interval timer interrupt (SPR 411)         */
    li       r, ivor12_handler@l
    mtivor12 r   /**< Watchdog timer interrupt (SPR 412)               */
    li       r, ivor13_handler@l
    mtivor13 r   /**< Data TLB error interrupt (SPR 413)               */
    li       r, ivor14_handler@l
    mtivor14 r   /**< Instruction TLB error interrupt (SPR 414)        */
    li       r, ivor15_handler@l
    mtivor15 r   /**< Debug interrupt (SPR 415)                        */
    li       r, ivor32_handler@l
    mtivor32 r   /**< SPE APU unavailable interrupt (SPR 528)          */
    li       r, ivor33_handler@l
    mtivor33 r   /**< SPE floating-point data exception int (SPR 529)  */
    li       r, ivor34_handler@l
    mtivor34 r   /**< SPE floating-point round exception int (SPR 530) */
  }

  INTC.MCR.R = 0;                       /**< s/w mode, 4byte entry size */
  INTC.IACKR.R = (uint32_t)vectors;     /**< set base                   */
  INTC.CPR.B.PRI = 0;                   /**< unmask                     */

  asm( mfmsr r );
  r |= INITIAL_MSR;
  asm( mtmsr r );

  decr_1khz();
  PIT.PITMCR.B.FRZ = 1;             /**< freeze PIT timers in debug mode */

  edma_init();
}

/* --| INTERNAL |--------------------------------------------------------- */