/**
 * @file       weak_ivor_handlers.c
 * @headerfile core_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "platform/core/mpc5634m/core_prv.h"

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @brief default ivor0 handler, override as desired
 * @note Critical input (SPR 400)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor0_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor1 handler, override as desired
 * @note Machine check interrupt (SPR 401)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor1_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor2 handler, override as desired
 * @note Data storage interrupt (SPR 402)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor2_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor3 handler, override as desired
 * @note Instruction storage interrupt (SPR 403)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor3_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor4 handler, override as desired
 * @note  External input interrupt (SPR 404)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor4_handler( void )
{
  asm( "@here: b @here" );
}

/**
 * @brief default ivor5 handler, override as desired
 * @note Alignment interrupt (SPR 405)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor5_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor6 handler, override as desired
 * @note Program interrupt (SPR 406)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor6_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor7 handler, override as desired
 * @note Floating-point unavailable interrupt (SPR 407)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor7_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor8 handler, override as desired
 * @note System call interrupt (SPR 408)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor8_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor9 handler, override as desired
 * @note Auxiliary processor (SPR 409)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor9_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor10 handler, override as desired
 * @note Decrementer interrupt (SPR 410)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor10_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor11 handler, override as desired
 * @note Fixed-interval timer interrupt (SPR 411)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor11_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor12 handler, override as desired
 * @note Watchdog timer interrupt (SPR 412)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor12_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor13 handler, override as desired
 * @note Data TLB error interrupt (SPR 413)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor13_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor14 handler, override as desired
 * @note Instruction TLB error interrupt (SPR 414)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor14_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor15 handler, override as desired
 * @note Debug interrupt (SPR 415)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor15_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor32 handler, override as desired
 * @note SPE APU unavailable interrupt (SPR 528)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor32_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor33 handler, override as desired
 * @note SPE floating-point data exception interrupt (SPR 529)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor33_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop

/**
 * @brief default ivor34 handler, override as desired
 * @note SPE floating-point round exception interrupt (SPR 530)
 */
#pragma push
#pragma section code_type ".handlers"
#pragma function_align 16
__declspec(interrupt)
__declspec(weak)
__declspec(section ".handlers")
void
  ivor34_handler( void )
{
  asm( "@here: b @here" );
}
#pragma pop
