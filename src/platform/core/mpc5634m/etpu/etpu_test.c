/**************************************************************************
 * FILE NAME: $RCSfile: etpu_test.c,v $      COPYRIGHT (c) FREESCALE 2004 *
 * DESCRIPTION:                                     All Rights Reserved   *
 * This file contains the ETPU Test Function API.                         *
 *========================================================================*
 * ORIGINAL AUTHOR: Geoff Emerson (r47354)                                *
 * $Log: etpu_test.c,v $
 * Revision 2.2  2004/12/20 08:23:26  r47354
 * Removed unused pba8.
 *
 * Revision 2.1  2004/12/08 12:54:17  r47354
 * Fix comments
 *
 * Revision 2.0  2004/12/07 15:17:43  r47354
 * no message
 *
 * Revision 1.2  2004/12/07 14:45:29  r47354
 * Changes to remove etpu_config.h from builds.
 *
 * Revision 1.1  2004/11/11 13:51:54  r47354
 * Initial version.
 *
 *........................................................................*
 * 0.0    G. Emerson   27/Apr/04    Initial version.                      *
 * 0.1    G. Emerson   9/July/04    Only allocate new PRAM if channel     *
 *                                  has not been used before              *
 *                                  Allow for compiler #pragma issue      *
 * 0.2    G. Emerson   16/July/04    Support new build structure          *
 * 0.3    G.Emerson    16/July/04   Add Disclaimer                        *
 * 0.4    G. Emerson     1/Nov/04   Remove path in #include               *
 *                                  Remove debug comments                 *
 *                                  Remove #include for "etpu_qom.h       *
 **************************************************************************/
#include "etpu/etpu_util.h"          /* Utility routines for working eTPU */
#include "etpu/etpu_test.h"          /* TEST API header file */
extern uint32_t fs_etpu_data_ram_start;

/******************************************************************************
FUNCTION     : etpu_test
PURPOSE      : To initialize an eTPU channel to generate a PWM output.
INPUTS NOTES : This function has 3 parameters:
               channel - This is the channel number.
                           0-31 for ETPU_A and 64-95 for ETPU_B.
               Link channel - The Channel which will be sent a Link.
               test_feature - The  particular test feature to be generated.
               		            This parameter should be assigned a value of:
			                        FS_ETPU_TEST_GENERATE_INTERRUPT,
			                        FS_ETPU_TEST_GENERATE_DTR,
			                        FS_ETPU_TEST_GENERATE_LINK,
			                        FS_ETPU_TEST_GLOBAL_EXCEPTION.
RETURNS NOTES: Error code if channel could not be initialized. Error code that
                 can be returned is: FS_ETPU_ERROR_MALLOC
******************************************************************************/

int32_t fs_etpu_test (uint8_t channel, uint8_t Link_channel,
                      uint8_t test_feature)
{
    uint32_t *pba;              /* base address for channel */

/* disable channel before changing anything else */
    fs_etpu_disable (channel);

    if (eTPU->CHAN[channel].CR.B.CPBA == 0)
      {
          /* get parameter RAM
             number of parameters passed from eTPU C code */
          pba = fs_etpu_malloc (ETPU_TEST_NUM_PARMS);

          if (pba == 0)
            {
                return (FS_ETPU_ERROR_MALLOC);
            }
      }
    else                        /*set pba to what is in the CR register */
      {
          pba = fs_etpu_data_ram (channel);
      }

    *(pba + ((ETPU_TEST_CHANNEL_OFFSET - 1) >> 2)) = (uint24_t) Link_channel;

/*write chan config register*/
    eTPU->CHAN[channel].CR.R =
        (FS_ETPU_PRIORITY_MIDDLE << 28) + (ETPU_TEST_TABLE_SELECT << 24) +
        (ETPU_TEST_FUNCTION_NUMBER << 16) + (((uint32_t)pba -
        fs_etpu_data_ram_start) >> 3);

    eTPU->CHAN[channel].HSRR.R = test_feature;

    return (0);
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
