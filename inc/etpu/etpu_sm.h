/*************************************************************************
 * FILE NAME: $RCSfile: etpu_sm.h,v $        COPYRIGHT (c) FREESCALE 2004
 * DESCRIPTION:                                     All Rights Reserved
 * This file contains the prototypes and defines for the eTPU
 * Stepper Motor (SM) API.
 *========================================================================
 * ORIGINAL AUTHOR: Milan Brejl (r54529)
 * $Log: etpu_sm.h,v $
 * Revision 1.2  2004/12/15 10:17:16  r54529
 * Changes to remove etpu_config.h from builds.
 *
 *........................................................................
 * REV      AUTHOR      DATE        DESCRIPTION OF CHANGE
 * ---   -----------  ----------    ---------------------
 * 0.1   M. Brejl     19/Mar/04     Initial version.
 * 0.2   M. Brejl     30/Jun/04     init method split into int + enable,
 *                                  disabled method added.
 *                                  Tested with "3-phase SM Demo".
 * 0.3   M. Brejl     13/Aug/04     Ported to new etpu dir structure.
 * 0.4   M. Brejl     05/Oct/04     Enable/Disable methods improved.
 * 1.0   M. Brejl     25/Nov/04     Updated for CVS and checked into CVS.
 * 2.0   M. Brejl     12/Dec/04
 * 2.1   M. Brejl     25/Oct/06     Load expressions added.
 **************************************************************************/
#ifndef _FS_ETPU_SM_H_
#define _FS_ETPU_SM_H_

#include "platform/core/mpc5634m/etpu/cpu/etpu_sm_auto.h"  /* Auto generated header file */

/*************************************************************************
*                            Definitions
*************************************************************************/

/* configuration options */
#define FS_ETPU_SM_2PHASE_FULL_STEP       0  // 2-phase full-step
#define FS_ETPU_SM_2PHASE_HALF_STEP       1  // 2-phase half-step
#define FS_ETPU_SM_3PHASE_FULL_STEP       2  // 3-phase full-step
#define FS_ETPU_SM_3PHASE_HALF_STEP       3  // 3-phase half-step
#define FS_ETPU_SM_EXT_DRIVER             4  // External driver

/* disable polarity options */
#define FS_ETPU_SM_DISABLE_LOW            FS_ETPU_SM_STOP_LOW
#define FS_ETPU_SM_DISABLE_HIGH           FS_ETPU_SM_STOP_HIGH

/*===================== Predifined configurations ======================*/
/*====== The FS_ETPU_SM_2PHASE_FULL_STEP configuration predefines: =====*/
#define FS_ETPU_SM_CFG_0_CHANNELS        2
#define FS_ETPU_SM_CFG_0_FM              FS_ETPU_SM_FULL_STEP
#define FS_ETPU_SM_CFG_0_PIN_SEQUENCE    0x333333
   /* can be replaced by rotated versions: 0x666666, 0xCCCCCC, 0x999999 */

/*====== The FS_ETPU_SM_2PHASE_HALF_STEP configuration predefines: =====*/
#define FS_ETPU_SM_CFG_1_CHANNELS        4
#define FS_ETPU_SM_CFG_1_FM              FS_ETPU_SM_HALF_STEP
#define FS_ETPU_SM_CFG_1_PIN_SEQUENCE    0x070707
   /* can be replaced by rotated versions:
   0x0E0E0E, 0x1C1C1C, 0x383838, 0x707070, 0xE0E0E0, 0x1C1C1C, 0x383838 */

/*====== The FS_ETPU_SM_3PHASE_FULL_STEP configuration predefines: =====*/
#define FS_ETPU_SM_CFG_2_CHANNELS        6
#define FS_ETPU_SM_CFG_2_FM              FS_ETPU_SM_FULL_STEP
#define FS_ETPU_SM_CFG_2_PIN_SEQUENCE    0x0C30C3
   /* can be replaced by rotated versions:
                       0x186186, 0x30C30C, 0x618618, 0xC30C30, 0x861861 */

/*====== The FS_ETPU_SM_3PHASE_HALF_STEP configuration predefines: =====*/
#define FS_ETPU_SM_CFG_3_CHANNELS        6
#define FS_ETPU_SM_CFG_3_FM              FS_ETPU_SM_HALF_STEP
#define FS_ETPU_SM_CFG_3_PIN_SEQUENCE    0x070070
   /* can be replaced by rotated versions:
             0x00E00E, 0x01C01C, 0x038038, 0x007007, 0x0E00E0, 0x1C01C0,
                       0x380380, 0x700700, 0xE00E00, 0xC01C01, 0x803803 */

/*====== The FS_ETPU_SM_EXT_DRIVER configuration predefines: ===========*/
#define FS_ETPU_SM_CFG_4_CHANNELS        1
#define FS_ETPU_SM_CFG_4_FM              FS_ETPU_SM_FULL_STEP
#define FS_ETPU_SM_CFG_4_PIN_SEQUENCE    0xAAAAAA
   /* can be replaced by rotated versions: 0x555555 */

/*************************************************************************
*                       Function Prototypes
*************************************************************************/

/******************************************************************************
*FUNCTION     : fs_etpu_sm_init
*PURPOSE      : To initialize eTPU channels to drive Stepper Motor.
*INPUTS NOTES : This function has 8 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               configuration  - This is the predefined configuration parameter.
*                                This parameter should be assigned a value of:
*                                FS_ETPU_SM_2PHASE_FULL_STEP or
*                                FS_ETPU_SM_2PHASE_HALF_STEP or
*                                FS_ETPU_SM_3PHASE_FULL_STEP or
*                                FS_ETPU_SM_3PHASE_HALF_STEP or
*                                FS_ETPU_SM_EXT_DRIVER
*               start_position - This is the starting current_position value.
*               start_period   - Start period as number of TCR1 ticks.
*                                Start period is the first and the last step
*                                period of a movement.
*               slew_period    - Slew period as number of TCR1 ticks.
*                                Slew period is the step period when the motor
*                                rotates at max speed - the shortest period
*                                of a movement.
*               *p_accel_tbl   - This parameter is the pointer to
*                                an Acceleration Table. The Acceleration Table
*                                is an array of unsigned fract16.
*               accel_tbl_size - This parameter is the Acceleration Table size
*                                as number of 16-bit acceleration steps.
*
*RETURNS NOTES: Error code if channel could not be initialized. Error codes that
*               can be returned are: FS_ETPU_ERROR_MALLOC.
*WARNING      : This function does not configure the pin, only the eTPU. In a
*               system a pin may need to be configured to select the eTPU.
******************************************************************************/
int32_t fs_etpu_sm_init( uint8_t   channel,
                         uint8_t   configuration,
                         int24_t   start_position,
                         uint24_t  start_period,
                         uint24_t  slew_period,
                   const uint16_t *p_accel_tbl,
                         uint16_t  accel_tbl_size );

/******************************************************************************
*FUNCTION     : fs_etpu_sm_enable
*PURPOSE      : To initialize all channel according to actual pin_sequence,
*               and enable.
*INPUTS NOTES : This function has 2 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               priority - This is the priority to assign to the channels.
*                          This parameter should be assigned a value of:
*                          FS_ETPU_PRIORITY_HIGH, FS_ETPU_PRIORITY_MIDDLE or
*                          FS_ETPU_PRIORITY_LOW.
******************************************************************************/
void fs_etpu_sm_enable( uint8_t channel, uint8_t priority);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_disable
*PURPOSE      : To turn all channel pins to inactive polarity, and disable.
*INPUTS NOTES : This function has 2 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               polarity - This is the polarity of generated signals.
*                          This parameter can be assigned a value of:
*                          FS_ETPU_SM_DISABLE_LOW or
*                          FS_ETPU_SM_DISABLE_HIGH
******************************************************************************/
void fs_etpu_sm_disable( uint8_t channel, uint8_t polarity);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_set_dp
*PURPOSE      : To set a new desired position and make the motor move there.
*INPUTS NOTES : This function has 2 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               desired_position - This is the new desired_position value.
******************************************************************************/
void fs_etpu_sm_set_dp( uint8_t channel, int24_t desired_position);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_set_sp
*PURPOSE      : To set the slew period.
*INPUTS NOTES : This function has 2 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               slew_period - This is the new slew_period value as number of
*                             TCR1 ticks. Slew period is the step period when
*                             the motor rotates at max speed - the shortest
*                             period of a movement.
******************************************************************************/
void fs_etpu_sm_set_sp( uint8_t channel, int24_t slew_period);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_get_dp
*PURPOSE      : To get the desired_position.
*INPUTS NOTES : This function has 1 parameter:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*
*RETURNS NOTES: The function returns the desired_position (uint24_t).
******************************************************************************/
int24_t fs_etpu_sm_get_dp( uint8_t channel);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_get_cp
*PURPOSE      : To get the current_position.
*INPUTS NOTES : This function has 1 parameter:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*
*RETURNS NOTES: The function returns the current_position (uint24_t).
******************************************************************************/
int24_t fs_etpu_sm_get_cp( uint8_t channel);

/******************************************************************************
*FUNCTION     : fs_etpu_sm_get_flags
*PURPOSE      : To get the status flags.
*INPUTS NOTES : This function has 1 parameter:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*
*RETURNS NOTES: The function returns the status byte.
*
*EXAMPLE      : Use these examples to test the status byte:
* if ((flags & FS_ETPU_SM_STEPPING) == FS_ETPU_SM_STEPPING_ON) ... if stepping
* if ((flags & FS_ETPU_SM_STEPPING) == FS_ETPU_SM_STEPPING_OFF) ... if not stepping
* if ((flags & FS_ETPU_SM_DIRECTION) == FS_ETPU_SM_DIRECTION_DEC) ... if going decremental
* if ((flags & FS_ETPU_SM_DIRECTION) == FS_ETPU_SM_DIRECTION_INC) ... if going incremental
* if ((flags & FS_ETPU_SM_SLEW) == FS_ETPU_SM_SLEW_ON) ... if in slew rate
* if ((flags & FS_ETPU_SM_SLEW) == FS_ETPU_SM_SLEW_OFF) ... if not in slew rate
******************************************************************************/
uint8_t fs_etpu_sm_get_flags( uint8_t channel);


/*=============== TPU3 API Compatibility Functions =====================*/
//
///* SM initialization */
//void tpu_tsm_init( struct  TPU3_tag *tpu,
//                   UINT8   channel,
//                   UINT8   priority,
//                   INT16   start_position,
//                   UINT16  table_size_index,
//                   UINT16  slew_period,
//                   UINT16  start_period,
//                   UINT16  pin_sequence,
//                   UINT8   number_channels,
//                   UINT16 *table,
//                   UINT8   table_size);
//
///* "move" command */
//void tpu_tsm_mov(struct TPU3_tag *tpu, UINT8 channel, UINT16 position);
//
///* read DESIRED POSITION */
//UINT16 tpu_tsm_rd_dp(struct TPU3_tag *tpu, UINT8 channel);
//
///* read CURRENT POSITION */
//UINT16 tpu_tsm_rd_cp(struct TPU3_tag *tpu, UINT8 channel);
//
/*******************************************************************************
*        Information for eTPU Graphical Configuration Tool
*******************************************************************************/
/* full function name: SM - Stepper Motor */
/* channel assignment when (configuration=FS_ETPU_SM_2PHASE_FULL_STEP); load: sm2f
     A_master = channel
     B_slave  = channel + 1
*/
/* channel assignment when (configuration=FS_ETPU_SM_2PHASE_HALF_STEP); load: sm2h
     A_master = channel
     B_slave  = channel + 1
     C_slave  = channel + 2
     D_slave  = channel + 3
*/
/* channel assignment when (configuration=FS_ETPU_SM_3PHASE_FULL_STEP); load: sm3f
     A_master = channel
     B_slave  = channel + 1
     C_slave  = channel + 2
     D_slave  = channel + 3
     E_slave  = channel + 4
     F_slave  = channel + 5
*/
/* channel assignment when (configuration=FS_ETPU_SM_3PHASE_HALF_STEP); load: sm3h
     A_master = channel
     B_slave  = channel + 1
     C_slave  = channel + 2
     D_slave  = channel + 3
     E_slave  = channel + 4
     F_slave  = channel + 5
*/
/* channel assignment when (configuration=FS_ETPU_SM_EXT_DRIVER); load: smext
     A_master = channel
*/

/* load expression sm2f
step_base = 100*etpu_tcr1_freq/(slew_period*etpu_clock_freq)
A_master = (208+30*2)*step_base
B_slave  = 0
*/
/* load expression sm2h
step_base = 100*etpu_tcr1_freq/(slew_period*etpu_clock_freq)
A_master = (208+32*4)*step_base
B_slave  = 0
C_slave  = 0
D_slave  = 0
*/
/* load expression sm3f
step_base = 100*etpu_tcr1_freq/(slew_period*etpu_clock_freq)
A_master = (208+30*6)*step_base
B_slave  = 0
C_slave  = 0
D_slave  = 0
E_slave  = 0
F_slave  = 0
*/
/* load expression sm3h
step_base = 100*etpu_tcr1_freq/(slew_period*etpu_clock_freq)
A_master = (208+32*6)*step_base
B_slave  = 0
C_slave  = 0
D_slave  = 0
E_slave  = 0
F_slave  = 0
*/
/* load expression smext
step_base = 100*etpu_tcr1_freq/(slew_period*etpu_clock_freq)
A_master = (208+30)*step_base
*/

#endif
/*********************************************************************
 *
 * Copyright:
 *	Freescale Semiconductor, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Freescale
 *  Semiconductor, Inc. This software is provided on an "AS IS"
 *  basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, Freescale
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH
 *  REGARD TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF)
 *  AND ANY ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Freescale Semiconductor assumes no responsibility for the
 *  maintenance and support of this software
 ********************************************************************/

