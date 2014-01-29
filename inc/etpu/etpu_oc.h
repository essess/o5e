/**************************************************************************
 * FILE NAME: $RCSfile: etpu_oc.h,v $        COPYRIGHT (c) FREESCALE 2004 *
 * DESCRIPTION:                                     All Rights Reserved   *
 * This file contains the prototypes and defines for the ETPU Output      *
 * Compare (OC) API                                                       *
 *========================================================================*
 * ORIGINAL AUTHOR: Geoff Emerson (r47354)                                *
 * $Log: etpu_oc.h,v $
 * Revision 1.4  2005/02/04 14:05:57  r47354
 * Major update based on how new etpuc code works.
 *
 * Revision 1.3  2004/12/07 14:01:46  r47354
 * Added more comments to fs_etpu_oc_data.
 *
 * Revision 1.2  2004/12/07 13:12:35  r47354
 * Updates as per QOM API rel_2_1
 *
 *........................................................................*
 * 0.1   G. Emerson   21/May/04     Initial version.                      *
 * 0.2                              Updated for new build structure.      *
 * 0.3   G.Emerson  16/July/04 Add Disclaimer                             *
 **************************************************************************/

#include "platform/core/mpc5634m/etpu/cpu/etpu_oc_auto.h"		/*Auto generated header file for eTPU OC*/

/**************************************************************************/
/*                            Definitions                                 */
/**************************************************************************/

struct offset {
  int :7;
	int offset:22;
	int pin_action_capture_timebase:3;
	} ;

struct Match_and_Actual_times
{
int32_t MatchTime1,
        MatchTime2,
        ActualTime1,
        ActualTime2;
};


/**************************************************************************/
/*                       Function Prototypes                              */
/**************************************************************************/

/* OC channel initialization */

/* OC channel initialization, immediate mode */
/***************************************************************************/

uint8_t fs_etpu_oc_init_immed (uint8_t channel, uint8_t priority,
                               uint8_t match_timebase,
                               uint32_t offset1, uint8_t pin_action_capture_timebase1,
                               uint32_t offset2, uint8_t pin_action_capture_timebase2,
                               uint8_t init_pin);

/* OC channel initialization, reference mode*/
uint8_t fs_etpu_oc_init_ref (uint8_t channel, uint8_t priority,
                               uint8_t match_timebase,
                               uint32_t offset1, uint8_t pin_action_capture_timebase1,
                               uint32_t offset2, uint8_t pin_action_capture_timebase2,
                               uint8_t init_pin,
                               uint32_t * ref);

/* OC channel initialization, value mode */
uint8_t fs_etpu_oc_init_value (uint8_t channel, uint8_t priority,
                               uint8_t match_timebase,
                               uint32_t value, uint8_t pin_action_capture_timebase1,
                               uint32_t offset2, uint8_t pin_action_capture_timebase2,
                               uint8_t init_pin
                               );

/***************************************************************************/
/* OC infromation function */

/* Match and Actual event times */
void fs_etpu_oc_data(uint8_t channel, struct Match_and_Actual_times *these_time);

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
