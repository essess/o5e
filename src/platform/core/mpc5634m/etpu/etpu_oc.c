/**************************************************************************
 * FILE NAME: $RCSfile: etpu_oc.c,v $        COPYRIGHT (c) FREESCALE 2004 *
 * DESCRIPTION:                                     All Rights Reserved   *
 * This file contains  ETPU  Output Compare (OC) API                      *
 *========================================================================*
 * ORIGINAL AUTHOR: Geoff Emerson (r47354)                                *
 * $Log: etpu_oc.c,v $
 * Revision 2.3  2005/03/30 07:25:43  r47354
 * Fix typo in comments: FS_OC_MATCH_TCR1 --> FS_OC_MATCH_TCR2
 *
 * Revision 2.2  2005/03/16 16:37:34  r47354
 * Post review tidy up.
 *
 * Revision 2.1  2005/02/04 14:26:59  r47354
 * Major update based on how new etpuc code works.
 *
 * Revision 2.0  2004/12/07 14:03:08  r47354
 * no message
 *
 * Revision 1.3  2004/12/07 14:01:07  r47354
 * Formatting tidy up
 *
 * Revision 1.2  2004/12/07 13:12:35  r47354
 * Updates as per QOM API rel_2_1
 *
 *........................................................................*
 * 0.1   G. Emerson   21/May/04     Initial version.                      *
 * 0.2   G. Emerson   21/May/04     Disable channel to begin with         *
 * 0.3                              Updated for new build structure.      *
 * 0.4   G.Emerson  25/June/04 Add FS_ prefix to following macros         *
 *                             ETPU_QOM_TABLE_START_PTR_OFFSET            *
 *                             ETPU_QOM_TABLE_END_PTR_OFFSET              *
 *                             ETPU_QOM_LOOP_COUNT_OFFSET                 *
 *                             ETPU_QOM_OPTION_OFFSET                     *
 *                             ETPU_QOM_REF_ADDR_PTR_OFFSET               *
 *                             ETPU_QOM_FUNCTION_NUMBER                   *
 *                             ETPU_QOM_TABLE_SELECT                      *
 *                             ETPU_QOM_NUM_PARMS                         *
 *                             ETPU_QOM_LAST_MATCH_TIME_OFFSET            *
 * 0.5   G.Emerson  16/July/04 Add Disclaimer                             *
 **************************************************************************/
#include "etpu/etpu_util.h"          /* Utility routines for working with the eTPU */
#include "etpu/etpu_oc.h"            /* eTPU QOM API */
extern uint32_t fs_etpu_data_ram_start;
/**************************************************************************
FUNCTION     : fs_etpu_oc_init_immed
PURPOSE      : To initialize an eTPU channel to generate an immediate OC output.
INPUTS NOTES : This function has 8 parameters:
               channel - This is the channel number.
                         0-31 for ETPU_A and 64-95 for ETPU_B.
              priority - This is the priority to assign to the channel.
                         This parameter should be assigned a value of:
                          FS_ETPU_PRIORITY_HIGH,
                          FS_ETPU_PRIORITY_MIDDLE,
                          FS_ETPU_PRIORITY_LOW.
        match_timebase - Timebase for matches.Valid values are:
            		          FS_OC_MATCH_TCR1
            		          FS_OC_MATCH_TCR2.
              offset1 -  The number of TCR counts from now to the first event.
pin_action_capture_timebase1 - Pin Action at first match and first capture
	                                 timebase selection. Valid values are.
	                                 This parameter should be assigned a value of:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              offset2 - The number of TCR counts from the first event to the
                        second event.
pin_action_capture_timebase2 -  Pin Action at second match and second capture
	                                 timebase selection. Valid values are:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              init_pin - The  state  the pin is driven to at initialisation.
               		       This parameter should be assigned a value of:
               		        FS_ETPU_OC_INIT_PIN_LOW
               		        FS_ETPU_OC_INIT_PIN_HIGH
               		        FS_ETPU_OC_INIT_PIN_NO_CHANGE.
******************************************************************************
RETURNS NOTES: Error code is channel could not be initialized. Error code that
                 can be returned is: FS_ETPU_ERROR_MALLOC
WARNING      : This function does not configure the pin, only the eTPU. In a
                  system a pin may need to be configured to select the eTPU.
******************************************************************************/

uint8_t fs_etpu_oc_init_immed (uint8_t channel, uint8_t priority,
                               uint8_t match_timebase,
                               uint32_t offset1, uint8_t pin_action_capture_timebase1,
                               uint32_t offset2, uint8_t pin_action_capture_timebase2,
                               uint8_t init_pin)
{
    uint32_t *pba;              /*parameter base address for channel */
    uint8_t *pba8;

/* disable channel before changing anything else */
    fs_etpu_disable (channel);

/*only get parameter RAM if the channel has not been used before */

    if (eTPU->CHAN[channel].CR.B.CPBA == 0)
      {

          /* get parameter RAM
             number of parameters passed from eTPU C code */
          pba = fs_etpu_malloc (FS_ETPU_OC_NUM_PARMS);

          if (pba == 0)
            {
                return (FS_ETPU_ERROR_MALLOC);
            }
      }
    else                        /*set pba to what is in the CR register */
      {
          pba = fs_etpu_data_ram (channel);
      }

    pba8 = (uint8_t *) pba;

/*write parameters*/

    *(pba + ((FS_ETPU_OC_OFFSET1_OFFSET-1)>>2)) = (uint24_t) (offset1);
    *(pba + ((FS_ETPU_OC_OFFSET2_OFFSET-1)>>2)) = (uint24_t) (offset2);
    *(pba8 + FS_ETPU_OC_EVENT1_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase1);
    *(pba8 + FS_ETPU_OC_EVENT2_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase2);
    *(pba8 + FS_ETPU_OC_MATCH_TIMEBASE ) = (uint8_t) (match_timebase);

/*write hsr*/
    eTPU->CHAN[channel].HSRR.R = init_pin;

    eTPU->CHAN[channel].SCR.R = (FS_ETPU_OC_INIT_IMMED<<1);

/*write chan config register */
    eTPU->CHAN[channel].CR.R =
        (priority << 28) + (FS_ETPU_OC_TABLE_SELECT << 24) +
        (FS_ETPU_OC_FUNCTION_NUMBER << 16) + (((uint32_t) pba -
        fs_etpu_data_ram_start) >> 3);

    return (0);
}

/******************************************************************************
/******************************************************************************
/*FUNCTION     : fs_etpu_oc_init_value
/*PURPOSE      : To initialize an eTPU channel to generate an OC output
                 in value mode
INPUTS NOTES : This function has 8 parameters:
               channel - This is the channel number.
                         0-31 for ETPU_A and 64-95 for ETPU_B.
              priority - This is the priority to assign to the channel.
                         This parameter should be assigned a value of:
                          FS_ETPU_PRIORITY_HIGH,
                          FS_ETPU_PRIORITY_MIDDLE,
                          FS_ETPU_PRIORITY_LOW.
        match_timebase - Timebase for matches.Valid values are:
            		          FS_OC_MATCH_TCR1
            		          FS_OC_MATCH_TCR2.
              value -  The TCR count at which the first event will be scheduled
                       to occur.
pin_action_capture_timebase1 - Pin Action at first match and first capture
	                                 timebase selection. Valid values are.
	                                 This parameter should be assigned a value of:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              offset2 - The number of TCR counts from the first event to the
                        second event.
pin_action_capture_timebase2 -  Pin Action at second match and second capture
	                                 timebase selection. Valid values are:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              init_pin - The  state  the pin is driven to at initialisation.
               		       This parameter should be assigned a value of:
               		        FS_ETPU_OC_INIT_PIN_LOW
               		        FS_ETPU_OC_INIT_PIN_HIGH
               		        FS_ETPU_OC_INIT_PIN_NO_CHANGE.
*******************************************************************************
RETURNS NOTES: Error code is channel could not be initialized. Error code that
                 can be returned is: FS_ETPU_ERROR_MALLOC
WARNING      : This function does not configure the pin, only the eTPU. In a
                  system a pin may need to be configured to select the eTPU.
*******************************************************************************/
uint8_t fs_etpu_oc_init_value (uint8_t channel, uint8_t priority,
                               uint8_t match_timebase,
                               uint32_t value, uint8_t pin_action_capture_timebase1,
                               uint32_t offset2, uint8_t pin_action_capture_timebase2,
                               uint8_t init_pin
                               )
{
    uint32_t *pba;              /*parameter base address for channel */
    uint8_t *pba8;

/* disable channel before changing anything else */
    fs_etpu_disable (channel);

/*only get parameter RAM if the channel has not been used before */

    if (eTPU->CHAN[channel].CR.B.CPBA == 0)
      {

          /* get parameter RAM
             number of parameters passed from eTPU C code */
          pba = fs_etpu_malloc (FS_ETPU_OC_NUM_PARMS);

          if (pba == 0)
            {
                return (FS_ETPU_ERROR_MALLOC);
            }
      }
    else                        /*set pba to what is in the CR register */
      {
          pba = fs_etpu_data_ram (channel);
      }

    pba8 = (uint8_t *) pba;

/*write parameters*/

    *(pba + ((FS_ETPU_OC_OFFSET1_OFFSET-1)>>2)) = (uint24_t) (value);
    *(pba + ((FS_ETPU_OC_OFFSET2_OFFSET-1)>>2)) = (uint24_t) (offset2);
    *(pba8 + FS_ETPU_OC_EVENT1_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase1);
    *(pba8 + FS_ETPU_OC_EVENT2_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase2);
    *(pba8 + FS_ETPU_OC_MATCH_TIMEBASE ) = (uint8_t) (match_timebase);
/*write hsr*/
    eTPU->CHAN[channel].HSRR.R = init_pin;

    eTPU->CHAN[channel].SCR.R = FS_ETPU_OC_INIT_VALUE;

/*write chan config register */
    eTPU->CHAN[channel].CR.R =
        (priority << 28) + (FS_ETPU_OC_TABLE_SELECT << 24) +
        (FS_ETPU_OC_FUNCTION_NUMBER << 16) + (((uint32_t) pba -
        fs_etpu_data_ram_start) >> 3);

    return (0);
}
/******************************************************************************
FUNCTION     : fs_etpu_oc_init_ref
PURPOSE      : To initialize an eTPU channel to generate a OC output with
               respect to a reference value
INPUTS NOTES : This function has 8 parameters:
               channel - This is the channel number.
                         0-31 for ETPU_A and 64-95 for ETPU_B.
              priority - This is the priority to assign to the channel.
                         This parameter should be assigned a value of:
                          FS_ETPU_PRIORITY_HIGH,
                          FS_ETPU_PRIORITY_MIDDLE,
                          FS_ETPU_PRIORITY_LOW.
        match_timebase - Timebase for matches.Valid values are:
            		          FS_OC_MATCH_TCR1
            		          FS_OC_MATCH_TCR2.
              offset1 -  The number of TCR counts from now to the first event.
pin_action_capture_timebase1 - Pin Action at first match and first capture
	                                 timebase selection. Valid values are.
	                                 This parameter should be assigned a value of:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              offset2 - The number of TCR counts from the first event to the
                        second event.
pin_action_capture_timebase2 -  Pin Action at second match and second capture
	                                 timebase selection. Valid values are:
	                                 OC_PIN_LOW_CAPTURE_TCR1
                                   OC_PIN_LOW_CAPTURE_TCR2
                                   OC_PIN_HIGH_CAPTURE_TCR1
                                   OC_PIN_HIGH_CAPTURE_TCR2
                                   OC_PIN_TOGGLE_CAPTURE_TCR1
                                   OC_PIN_TOGGLE_CAPTURE_TCR2
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR1
                                   OC_PIN_NO_CHANGE_CAPTURE_TCR2
              init_pin - The  state  the pin is driven to at initialisation.
               		       This parameter should be assigned a value of:
               		        FS_ETPU_OC_INIT_PIN_LOW
               		        FS_ETPU_OC_INIT_PIN_HIGH
               		        FS_ETPU_OC_INIT_PIN_NO_CHANGE.
               		ref - The address of the reference count. The address specified
               		      should be relative to the eTPU's address space.
*******************************************************************************
RETURNS NOTES: Error code is channel could not be initialized. Error code that
                 can be returned is: FS_ETPU_ERROR_MALLOC
WARNING      : This function does not configure the pin, only the eTPU. In a
                  system a pin may need to be configured to select the eTPU.
******************************************************************************/
uint8_t fs_etpu_oc_init_ref (uint8_t channel, uint8_t priority,
                             uint8_t match_timebase,
                             uint32_t offset1, uint8_t pin_action_capture_timebase1,
                             uint32_t offset2, uint8_t pin_action_capture_timebase2,
                             uint8_t init_pin,
                             uint32_t * ref)
{
    uint32_t *pba;              /*parameter base address for channel */
    uint8_t *pba8;

/* disable channel before changing anything else */
    fs_etpu_disable (channel);

/*only get parameter RAM if the channel has not been used before */

    if (eTPU->CHAN[channel].CR.B.CPBA == 0)
      {

          /* get parameter RAM
             number of parameters passed from eTPU C code */
          pba = fs_etpu_malloc (FS_ETPU_OC_NUM_PARMS);

          if (pba == 0)
            {
                return (FS_ETPU_ERROR_MALLOC);
            }
      }
    else                        /*set pba to what is in the CR register */
      {
          pba = fs_etpu_data_ram (channel);
      }

    pba8 = (uint8_t *) pba;

/*write parameters*/

    *(pba + ((FS_ETPU_OC_OFFSET1_OFFSET-1)>>2)) = (uint24_t) (offset1);
    *(pba + ((FS_ETPU_OC_OFFSET2_OFFSET-1)>>2)) = (uint24_t) (offset2);
    *(pba8 + FS_ETPU_OC_EVENT1_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase1);
    *(pba8 + FS_ETPU_OC_EVENT2_OPTION_OFFSET ) =
          (uint8_t) (pin_action_capture_timebase2);
    *(pba8 + FS_ETPU_OC_MATCH_TIMEBASE ) = (uint8_t) (match_timebase);
    *(pba + ((FS_ETPU_OC_REF_ADDR_PTR_OFFSET - 1) >> 2)) = (uint24_t) ref;
/*write hsr*/
    eTPU->CHAN[channel].HSRR.R = init_pin;

    eTPU->CHAN[channel].SCR.R = (FS_ETPU_OC_INIT_REF <<1);

/*write chan config register */
    eTPU->CHAN[channel].CR.R =
        (priority << 28) + (FS_ETPU_OC_TABLE_SELECT << 24) +
        (FS_ETPU_OC_FUNCTION_NUMBER << 16) + (((uint32_t) pba -
        fs_etpu_data_ram_start) >> 3);

    return (0);
}

/******************************************************************************
FUNCTION     : fs_etpu_oc_data
PURPOSE      : To get the match and actual event times after the OC function
               has executed.
INPUTS NOTES : This function has 6 parameters:
               channel - This is the channel number.
                         0-31 for ETPU_A and 64-95 for ETPU_B.
              these_times - the address of a structure which the API will
                            populate with the match and actual event times for
                            both events.
******************************************************************************/
void fs_etpu_oc_data (uint8_t channel, struct Match_and_Actual_times *these_times)
{
    these_times->MatchTime1 =
        fs_etpu_get_chan_local_24s (channel,
                                    FS_ETPU_OC_MATCH1_OFFSET);
    these_times->MatchTime2 =
        fs_etpu_get_chan_local_24s (channel,
                                    FS_ETPU_OC_MATCH2_OFFSET);
    these_times->ActualTime1 =
        fs_etpu_get_chan_local_24s (channel,
                                    FS_ETPU_OC_ACTUAL1_OFFSET);
    these_times->ActualTime2 =
        fs_etpu_get_chan_local_24s (channel,
                                    FS_ETPU_OC_ACTUAL2_OFFSET);
}

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
