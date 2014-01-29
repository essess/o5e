/*************************************************************************
 * FILE NAME: $RCSfile: etpu_sm.c,v $        COPYRIGHT (c) FREESCALE 2004
 * DESCRIPTION:                                     All Rights Reserved
 * This file contains the eTPU Stepper Motor (SM) API.
 *========================================================================
 * ORIGINAL AUTHOR: Milan Brejl (r54529)
 * $Log: etpu_sm.c,v $
 * Revision 1.2  2004/12/15 10:17:01  r54529
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
 * 1.0   M. Brejl     25/Nov/04     Setting function parameters optimized.
 *                                  Updated for CVS and checked into CVS.
 * 2.0   M. Brejl     12/Dec/04     No Warnings. etpu_config.h not used.
 **************************************************************************/
#include "etpu/etpu_util.h"		      /* Utility routines for working with eTPU */
#include "etpu/etpu_sm.h"              /* eTPU SM API defines */
extern uint32_t fs_etpu_data_ram_start;

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
                         uint16_t  accel_tbl_size )
{
  uint32_t *pba;              /* Parameter Base Address */
  uint16_t *p_etpu_accel_tbl; /* Pointer to accel_tbl in PRAM */
  uint16_t  tbl_size;         /* Accel Table size in words */
  uint16_t  i;
  /* values based on "configuration" parameter */
  uint8_t   channels;
  uint32_t  func_mode;
  uint24_t  pin_seq;

  /***************************************
   * PRAM allocation.
   **************************************/
  if ((pba=fs_etpu_malloc(FS_ETPU_SM_NUM_PARMS))==0)
  {
     return(FS_ETPU_ERROR_MALLOC);
  }

  tbl_size = (uint16_t)(sizeof(int16_t)*accel_tbl_size);
  if((p_etpu_accel_tbl=(uint16_t *)fs_etpu_malloc(tbl_size))==0)
  {
     return(FS_ETPU_ERROR_MALLOC);
  }
  /* Copy the acceleration table to ETPU PRAM */
  fs_memcpy32((uint32_t*)p_etpu_accel_tbl, (uint32_t*)p_accel_tbl, tbl_size);

  /***************************************
   * Based on "configuration" ...
   **************************************/
  switch (configuration)
  {
    case FS_ETPU_SM_2PHASE_FULL_STEP:
      channels =  FS_ETPU_SM_CFG_0_CHANNELS;
      func_mode = FS_ETPU_SM_CFG_0_FM;
      pin_seq =   FS_ETPU_SM_CFG_0_PIN_SEQUENCE;
      break;
    case FS_ETPU_SM_2PHASE_HALF_STEP:
      channels =  FS_ETPU_SM_CFG_1_CHANNELS;
      func_mode = FS_ETPU_SM_CFG_1_FM;
      pin_seq =   FS_ETPU_SM_CFG_1_PIN_SEQUENCE;
      break;
    case FS_ETPU_SM_3PHASE_FULL_STEP:
      channels =  FS_ETPU_SM_CFG_2_CHANNELS;
      func_mode = FS_ETPU_SM_CFG_2_FM;
      pin_seq =   FS_ETPU_SM_CFG_2_PIN_SEQUENCE;
      break;
    case FS_ETPU_SM_3PHASE_HALF_STEP:
      channels =  FS_ETPU_SM_CFG_3_CHANNELS;
      func_mode = FS_ETPU_SM_CFG_3_FM;
      pin_seq =   FS_ETPU_SM_CFG_3_PIN_SEQUENCE;
      break;
    case FS_ETPU_SM_EXT_DRIVER:
      channels =  FS_ETPU_SM_CFG_4_CHANNELS;
      func_mode = FS_ETPU_SM_CFG_4_FM;
      pin_seq =   FS_ETPU_SM_CFG_4_PIN_SEQUENCE;
  }

  /***************************************
   * Write chan config registers.
   **************************************/
  /* master channel */
  eTPU->CHAN[channel].CR.R = (FS_ETPU_SM_TABLE_SELECT << 24) +
                             (FS_ETPU_SM_FUNCTION_NUMBER << 16) +
                             (((uint32_t)pba - fs_etpu_data_ram_start) >> 3);
  eTPU->CHAN[channel].SCR.R = func_mode;
  /* slave channels */
  for (i=1; i<channels; i++)
  {
    eTPU->CHAN[channel+i].CR.R = (FS_ETPU_SM_TABLE_SELECT << 24)+
                                 (FS_ETPU_SM_FUNCTION_NUMBER << 16) +
                                 (((uint32_t)pba - fs_etpu_data_ram_start) >> 3);
  }

  /***************************************
   * Write parameters.
   **************************************/
  *(pba + ((FS_ETPU_SM_CURRENTPOSITION_OFFSET - 1) >> 2)) = (uint24_t)start_position;
  *(pba + ((FS_ETPU_SM_DESIREDPOSITION_OFFSET - 1) >> 2)) = (uint24_t)start_position;
  *(pba + ((FS_ETPU_SM_STARTPERIOD_OFFSET     - 1) >> 2)) = (uint24_t)start_period;
  *(pba + ((FS_ETPU_SM_SLEWPERIOD_OFFSET      - 1) >> 2)) = (uint24_t)slew_period;
  *(pba + ((FS_ETPU_SM_CHANNELS_OFFSET        - 1) >> 2)) = (uint24_t)channels;
  *(pba + ((FS_ETPU_SM_PINSEQUENCE_OFFSET     - 1) >> 2)) =           pin_seq;
  *(pba + ((FS_ETPU_SM_ACCELTBL_OFFSET        - 1) >> 2)) = (uint24_t)p_etpu_accel_tbl - (uint24_t)fs_etpu_data_ram_start;
  *(pba + ((FS_ETPU_SM_ACCELTBLSIZE_OFFSET    - 1) >> 2)) = (uint24_t)accel_tbl_size;
  *((uint8_t *)pba + FS_ETPU_SM_FLAGS_OFFSET)             = 0;

  return(0);
}

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
void fs_etpu_sm_enable( uint8_t channel, uint8_t priority)
{
  uint8_t   i;
  uint8_t   channels;
  uint32_t  func_mode;
  uint24_t  pin_seq;

  /* Get number of channels */
  channels = (uint8_t)fs_etpu_get_chan_local_24(channel, FS_ETPU_SM_CHANNELS_OFFSET);

  /* Get FM */
  func_mode = eTPU->CHAN[channel].SCR.B.FM1;

  /* Read actual pin_sequence */
  pin_seq = fs_etpu_get_chan_local_24(channel, FS_ETPU_SM_PINSEQUENCE_OFFSET);

  /* Initialize channels according to actual "pin_sequence" */
  for (i=0; i<channels; i++)
  {
    if ((pin_seq & 0x000001) == 0)
      eTPU->CHAN[channel+i].HSRR.R = FS_ETPU_SM_INIT_LOW;
    else
      eTPU->CHAN[channel+i].HSRR.R = FS_ETPU_SM_INIT_HIGH;

    fs_etpu_enable((uint8_t)(channel+i), priority);

    if (func_mode == FS_ETPU_SM_FULL_STEP)
      pin_seq>>=1;
    else
      pin_seq>>=2;
  }
}

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
void fs_etpu_sm_disable( uint8_t channel, uint8_t polarity)
{
  uint8_t   i;
  uint8_t   channels;
  uint8_t   hsr;

  /* Get number of channels */
  channels = (uint8_t)fs_etpu_get_chan_local_24(channel, FS_ETPU_SM_CHANNELS_OFFSET);

  /* Disable all channels */
  hsr = polarity;
  for (i=0; i<channels; i++)
  {
    eTPU->CHAN[channel+i].HSRR.R = hsr;
    fs_etpu_disable((uint8_t)(channel+i));
  }
}

/******************************************************************************
*FUNCTION     : fs_etpu_sm_set_dp
*PURPOSE      : To set a new desired position and make the motor move there.
*INPUTS NOTES : This function has 2 parameters:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*               desired_position - This is the new desired_position value.
******************************************************************************/
void fs_etpu_sm_set_dp( uint8_t channel, int24_t desired_position)
{
  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_DESIREDPOSITION_OFFSET,
    (uint24_t)desired_position);
  fs_etpu_set_hsr(channel, FS_ETPU_SM_MOVE);
}

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
void fs_etpu_sm_set_sp( uint8_t channel, int24_t slew_period)
{
  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_SLEWPERIOD_OFFSET,
                            (uint24_t)slew_period);
}

/******************************************************************************
*FUNCTION     : fs_etpu_sm_get_dp
*PURPOSE      : To get the desired_position.
*INPUTS NOTES : This function has 1 parameter:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*
*RETURNS NOTES: The function returns the desired_position (uint24_t).
******************************************************************************/
int24_t fs_etpu_sm_get_dp( uint8_t channel)
{
  return(fs_etpu_get_chan_local_24s(channel,FS_ETPU_SM_DESIREDPOSITION_OFFSET));
}

/******************************************************************************
*FUNCTION     : fs_etpu_sm_get_cp
*PURPOSE      : To get the current_position.
*INPUTS NOTES : This function has 1 parameter:
*               channel  - This is the Stepper Motor (SM) master channel number.
*                          0-31 for ETPU_A and 64-95 for ETPU_B.
*
*RETURNS NOTES: The function returns the current_position (uint24_t).
******************************************************************************/
int24_t fs_etpu_sm_get_cp( uint8_t channel)
{
  return(fs_etpu_get_chan_local_24s(channel,FS_ETPU_SM_CURRENTPOSITION_OFFSET));
}

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
* if ((flags & FS_ETPU_SM_STEPPING) == FS_ETPU_SM_STEPPING_OF) ... if not stepping
* if ((flags & FS_ETPU_SM_DIRECTION) == FS_ETPU_SM_DIRECTION_DEC) ... if going decremental
* if ((flags & FS_ETPU_SM_DIRECTION) == FS_ETPU_SM_DIRECTION_INC) ... if going incremental
* if ((flags & FS_ETPU_SM_SLEW) == FS_ETPU_SM_SLEW_ON) ... if in slew rate
* if ((flags & FS_ETPU_SM_SLEW) == FS_ETPU_SM_SLEW_OFF) ... if not in slew rate
******************************************************************************/
uint8_t fs_etpu_sm_get_flags( uint8_t channel)
{
  return(fs_etpu_get_chan_local_8(channel, FS_ETPU_SM_FLAGS_OFFSET));
}

/*=============== TPU3 API Compatibility Functions =====================*/

///******************************************************************************
//FUNCTION     : tpu_tsm_init
//PURPOSE      : To initialize eTPU channels to drive Stepper Motor the TPU3 way.
//INPUTS NOTES : This function has 13 parameters:
//                 *tpu - This is a pointer to the TPU3 module to use. Not used.
//                 channel - This is the Stepper Motor (SM) master channel number.
//                           0-31 for ETPU_A and 64-95 for ETPU_B.
//                 priority - This is the priority to assign to TSM channels.
//                            This parameter should be assigned a value of:
//                            ETPU_PRIORITY_HIGH, ETPU_PRIORITY_MIDDLE or
//                            ETPU_PRIORITY_LOW.
//                 start_position - This is the starting current_position.
//                 table_size_index - initialize the number of bytes in the table
//                            (upper 8 bits) and the index (lower 8 bits).
//                             The index (lower 8 bits) must be set to zero.
//                 slew_period - initializes the slew_period and S.
//                 start_period - initializes the start_period and A.
//                 pin_sequence - initializes the pin_sequence.
//                 number_channels - number of channels used for this TSM.
//                            Two to four channels total, including the master
//                            channel and the parameter table channels.
//                 *table - pointer to the table beginning location.
//                 table_size - Not used.
//RETURNS NOTES : none
//******************************************************************************/
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
//                   UINT8   table_size)
//{
//  uint32_t* pba;               // Parameter Base Address
//   int32_t  error_code = 0;    // Error code.
//  uint32_t func_mode;
//  uint8_t  i;
//
//  if (number_channels == 2)
//    func_mode = FS_ETPU_SM_FULL_STEP;
//  else if (number_channels == 4)
//    func_mode = FS_ETPU_SM_HALF_STEP;
//  else return;
//
//  /***************************************
//   * PRAM allocation.
//   **************************************/
//  if ((pba=fs_etpu_malloc(FS_ETPU_SM_NUM_PARMS))== 0) return;
//
//  /***************************************
//   * Write chan config registers.
//   **************************************/
//  /* master channel */
//  eTPU->CHAN[channel].CR.R = (priority << 28) + (FS_ETPU_SM_TABLE_SELECT << 24) +
//                             (FS_ETPU_SM_FUNCTION_NUMBER << 16) +
//                             (((uint32_t)pba - fs_etpu_data_ram_start) >> 3);
//  eTPU->CHAN[channel].SCR.R = func_mode;
//  /* slave channels */
//  for (i=1; i++; i<number_channels) {
//    eTPU->CHAN[channel+i].CR.R =
//                             (priority << 28) + (FS_ETPU_SM_TABLE_SELECT << 24) +
//                             (FS_ETPU_SM_FUNCTION_NUMBER << 16) +
//                             (((uint32_t)pba - fs_etpu_data_ram_start) >> 3);
//  }
//
//  /***************************************
//   * Write parameters.
//   **************************************/
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_CURRENTPOSITION_OFFSET, (uint24_t)start_position);
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_DESIREDPOSITION_OFFSET, (uint24_t)start_position);
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_STARTPERIOD_OFFSET, (uint24_t)(start_period>>1));
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_SLEWPERIOD_OFFSET, (uint24_t)(slew_period>>1));
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_CHANNELS_OFFSET, number_channels);
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_PINSEQUENCE_OFFSET, (uint24_t)((uint32_t)pin_sequence + pin_sequence<<16));
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_ACCELTBL_OFFSET, (uint16_t)table);
//  fs_etpu_set_chan_local_24(channel, FS_ETPU_SM_ACCELTBLSIZE_OFFSET, (uint24_t)(table_size_index>>8));
//  fs_etpu_set_chan_local_8 (channel, FS_ETPU_SM_FLAGS_OFFSET, 0);
//
//  /***************************************
//   * Write HSRs.
//   **************************************/
//  /* Initialize channels according to initial "pin_sequence" */
//  for (i=0; i++; i<number_channels) {
//    if ((pin_sequence & 0x0001) == 0)
//      eTPU->CHAN[channel].HSRR.R = FS_ETPU_SM_INIT_LOW;
//    else
//      eTPU->CHAN[channel].HSRR.R = FS_ETPU_SM_INIT_HIGH;
//
//    if (func_mode == FS_ETPU_SM_FULL_STEP)
//      pin_sequence>>=1;
//    else
//      pin_sequence>>=2;
//  }
//}
//
///*******************************************************************************
//FUNCTION      : tpu_tsm_mov
//PURPOSE       : To activate the move and acceleration of the stepper motor.
//INPUTS NOTES  : This function has 3 parameters:
//                 *tpu - This is a pointer to the TPU3 module to use. Not used.
//                 channel - This is the number of the master channel.
//                 position - The new desired position for the stepper motor.
//GENERAL NOTES : The channel must be a master channel for the TSM function. There
//                 can be more than one master channel in the same TPU. The
//                 additional master channel(s) would be for another TSM function.
//*******************************************************************************/
//void tpu_tsm_mov(struct TPU3_tag *tpu, UINT8 channel, UINT16 position)
//{
//  fs_etpu_sm_set_dp( (uint8_t)channel, (int24_t)position);
//}
//
///*******************************************************************************
//FUNCTION      : tpu_tsm_rd_dp
//PURPOSE       : To read the desired position.
//INPUTS NOTES  : This function has 2 parameters:
//                 *tpu - This is a pointer to the TPU3 module to use. Not used.
//                 channel - This is the number of the master channel
//RETURN NOTES  : desired position - The desired position is returned as a UINT16.
//GENERAL NOTES : The channel must be a master channel for the TSM function. The
//                 read of the desired position can be used to drive the program.
//*******************************************************************************/
//UINT16 tpu_tsm_rd_dp(struct TPU3_tag *tpu, UINT8 channel)
//{
//  return( (UINT16)fs_etpu_sm_get_dp( (uint8_t)channel));
//}
//
///*******************************************************************************
//FUNCTION      : tpu_tsm_rd_cp
//PURPOSE       : To read the current position.
//INPUTS NOTES  : This function has 2 parameters:
//                 *tpu - This is a pointer to the TPU3 module to use. Not used.
//                 channel - This is the number of the master channel
//RETURN NOTES  : current position - The desired position is returned as a UINT16.
//GENERAL NOTES : The channel must be a master channel for the TSM function. The
//                 read of the current position can be used to drive the program.
//*******************************************************************************/
//UINT16 tpu_tsm_rd_cp(struct TPU3_tag *tpu, UINT8 channel)
//{
//  return( (UINT16)fs_etpu_sm_get_cp( (uint8_t)channel));
//}

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
