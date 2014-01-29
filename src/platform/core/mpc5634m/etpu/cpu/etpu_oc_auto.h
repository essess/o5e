

/****************************************************************
 * WARNING this file is automatically generated DO NOT EDIT IT! *
 *                                                              *
 * FILE NAME: etpu_oc_auto.h       COPYRIGHT (c) Freescale 2004 *
 *                                      All Rights Reserved     *
 * This file generated by:                                      *
 * $RCSfile: etpuc_oc.c,v $ $Revision: 1.7 $
 *                                                              *
 * This file provides an interface between eTPU code and CPU    *
 * code. All references to the OC function should be made with  *
 * information in this file. This allows only symbolic          *
 * information to be referenced which allows the eTPU code to be*
 * optimized without effecting the CPU code.                    *
 ****************************************************************/
#ifndef _ETPU_OC_AUTO_H_
#define _ETPU_OC_AUTO_H_

/* Function Configuration Information */
#define FS_ETPU_OC_FUNCTION_NUMBER  2 
#define FS_ETPU_OC_TABLE_SELECT 1 
#define FS_ETPU_OC_NUM_PARMS 0x0020 

/* Host Service Request Definitions - init_pin options */
#define FS_ETPU_OC_INIT_PIN_LOW  1  
#define FS_ETPU_OC_INIT_PIN_HIGH 3 
#define FS_ETPU_OC_INIT_PIN_NO_CHANGE 7 

/* Match Timebase Selection - match_timebase options */
#define FS_OC_MATCH_TCR1  0  
#define FS_OC_MATCH_TCR2 1 

/* Capture Timebase Selection */
#define FS_OC_CAPTURE_TCR1  0  
#define FS_OC_CAPTURE_TCR2 1 

/* Function Mode0 Bit Definitions : Select Value mode*/
#define FS_ETPU_OC_INIT_VALUE 1 
/* Function Mode1 Bit Definitions : Select Immed/ref mode */
#define FS_ETPU_OC_INIT_IMMED 0 
#define FS_ETPU_OC_INIT_REF 1 

/* PinAction and time base selection definitions - pin_action_capture_timebase1 pin_action_capture_timebase2 options*/
#define FS_ETPU_OC_PIN_LOW_CAPTURE_TCR1  ((0 <<2) + (0 <<1) + 0 )
#define FS_ETPU_OC_PIN_LOW_CAPTURE_TCR2  ((0 <<2) + (0 <<1) + 1 )
#define FS_ETPU_OC_PIN_HIGH_CAPTURE_TCR1 ((1 <<2) + (0 <<1) + 0 )
#define FS_ETPU_OC_PIN_HIGH_CAPTURE_TCR2 ((1 <<2) + (0 <<1) + 1 )
#define FS_ETPU_OC_PIN_TOGGLE_CAPTURE_TCR1 ((0 <<2) + (1 <<1) + 0 )
#define FS_ETPU_OC_PIN_TOGGLE_CAPTURE_TCR2 ((0 <<2) + (1 <<1) + 1 )
#define FS_ETPU_OC_PIN_NO_CHANGE_CAPTURE_TCR1 ((1 <<2) + (1 <<1) + 0 )
#define FS_ETPU_OC_PIN_NO_CHANGE_CAPTURE_TCR2 ((1 <<2) + (1 <<1) + 1 )

/* Parameter Definitions */
#define FS_ETPU_OC_EVENT1_OPTION_OFFSET  0x0000
#define FS_ETPU_OC_OFFSET1_OFFSET  0x0001
#define FS_ETPU_OC_EVENT2_OPTION_OFFSET  0x0004
#define FS_ETPU_OC_OFFSET2_OFFSET  0x0005
#define FS_ETPU_OC_MATCH1_OFFSET  0x0009
#define FS_ETPU_OC_MATCH_TIMEBASE  0x0008
#define FS_ETPU_OC_MATCH2_OFFSET  0x000D
#define FS_ETPU_OC_ACTUAL1_OFFSET  0x0011
#define FS_ETPU_OC_ACTUAL2_OFFSET  0x0015
#define FS_ETPU_OC_REF_ADDR_PTR_OFFSET  0x0019

#endif

