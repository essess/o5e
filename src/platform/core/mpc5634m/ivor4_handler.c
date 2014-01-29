/**
 * @file       ivor4_handler.c
 * @headerfile core_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"
#include "platform/core/mpc5634m/mpc5634m.h"
#include "led.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @brief core ivor4 handler
 * @note  External input interrupt (SPR 404)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(section ".handlers")
asm void
  ivor4_handler( void )
{
enum
{
  INTC_IACKR = 0xfff48010ul,
  INTC_EOIR  = 0xfff48018ul
};
nofralloc
prolog:
  stwu    rsp, -0x50(rsp)   /* Create stack frame                                   */
  stw     r0, 0x24(rsp)     /* Store r0 working register                            */
  mfsrr1  r0                /* Store SRR1 (must be done before enabling EE)         */
  stw     r0, 0x10(rsp)
  mfsrr0  r0                /* Store SRR0 (must be done before enabling EE)         */
  stw     r0, 0x0C(rsp)
  stw     r12, 0x4C(rsp)    /* Store r12 NOW - we're going to use it                */
  lis     r12, INTC_IACKR@h /* Read pointer into ISR Vector Table & store in r12    */
  ori     r12, r12, INTC_IACKR@l
  lwz     r12, 0x0(r12)     /* Load INTC_IACKR, which clears request to processor   */
  lwz     r12, 0x0(r12)     /* Read ISR address from ISR Vector Table using pointer */
  /* Enable processor recognition of interrupts                                     */
  wrteei  1                 /* Set MSR[EE]=1                                        */
  /* Save rest of context required by EABI                                          */
  stw     r11, 0x48(rsp)    /* Store r11                                            */
  stw     r10, 0x44(rsp)    /* Store r10                                            */
  stw     r9, 0x40(rsp)     /* Store r9                                             */
  stw     r8, 0x3C(rsp)     /* Store r8                                             */
  stw     r7, 0x38(rsp)     /* Store r7                                             */
  stw     r6, 0x34(rsp)     /* Store r6                                             */
  stw     r5, 0x30(rsp)     /* Store r5                                             */
  stw     r3, 0x28(rsp)     /* Store r3                                             */
  stw     r4, 0x2C(rsp)     /* Store r4                                             */
  mfcr    r0                /* Store CR                                             */
  stw     r0, 0x20(rsp)
  mfxer   r0                /* Store XER                                            */
  stw     r0, 0x1C(rsp)
  mfctr   r0                /* Store CTR                                            */
  stw     r0, 0x18(rsp)
  mflr    r0                /* Store LR                                             */
  stw     r0, 0x14(rsp)

  /* Branch to ISR handler address from SW vector table                             */
  li      r3, LED_CPU_BUSY
  bl      led_on
  mtlr    r12               /* grab saved vector (we know led_on didn't touch it)   */
  blrl                      /* Branch to ISR, but return here                       */

epilog:
  /* Restore context required by EABI (except working registers)                    */
  lwz     r0, 0x14(rsp)     /* Restore LR                                           */
  mtlr    r0
  lwz     r0, 0x18(rsp)     /* Restore CTR                                          */
  mtctr   r0
  lwz     r0, 0x1C(rsp)     /* Restore XER                                          */
  mtxer   r0
  lwz     r0, 0x20(rsp)     /* Restore CR                                           */
  mtcr    r0
  lwz     r4, 0x2C(rsp)     /* Restore r4                                           */
  lwz     r5, 0x30(rsp)     /* Restore r5                                           */
  lwz     r6, 0x34(rsp)     /* Restore r6                                           */
  lwz     r7, 0x38(rsp)     /* Restore r7                                           */
  lwz     r8, 0x3C(rsp)     /* Restore r8                                           */
  lwz     r9, 0x40(rsp)     /* Restore r9                                           */
  lwz     r10, 0x44(rsp)    /* Restore r10                                          */
  lwz     r11, 0x48(rsp)    /* Restore r11                                          */
  lwz     r12, 0x4C(rsp)    /* Restore r12                                          */
  wrteei  0                 /* Disable processor recognition of interrupts          */
  lis     r3, INTC_EOIR@h   /* Load upper half of INTC_EOIR address to r4           */
  ori     r3, r3, INTC_EOIR@l
  stw     r3, 0(r3)           /* Write (anything) to INTC_EOIR to ack               */
  lwz     r3, 0x28(rsp)       /* Restore r3                                         */
  lwz     r0, 0x0C(rsp)       /* Restore SRR0                                       */
  mtsrr0  r0
  lwz     r0, 0x10(rsp)       /* Restore SRR1                                       */
  mtsrr1  r0
  lwz     r0, 0x24(rsp)       /* Restore r0                                         */
  addi    rsp, rsp, 0x50      /* Restore space on stack                             */
  rfi                         /* End of Interrupt                                   */
}
#pragma pop
