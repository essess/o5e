/**************************************************************************
 * FILE NAME: $RCSfile: etpu_app_eng_pos_mcam.h,v $                       *
 *                                           COPYRIGHT (c) FREESCALE 2013 *
 * DESCRIPTION:                                     All Rights Reserved   *
 * This file contains the prototypes and defines for the eTPU automotive  *
 * synchronisation functions.                                             *
 *========================================================================*
 * ORIGINAL AUTHOR: Milan Brejl (r54529)                                  *
 * $Log: etpu_app_eng_pos_mcam.h,v $
 * Revision 1.0  2013/01/25 09:53:27  r54529
 * Initial revision. Based on etpu_app_eng_pos.h.
 *
 **************************************************************************/
#include "platform/core/mpc5634m/etpu/cpu/etpu_mcam_auto.h"  /* Auto generated header file for eTPU mcam  */
#include "platform/core/mpc5634m/etpu/cpu/etpu_crank_auto.h" /* Auto generated header file for eTPU crank */

/**************************************************************************/
/*                       Function Prototypes                              */
/**************************************************************************/

/* eng_pos_mcam channel initialisation */
int32_t fs_etpu_app_eng_pos_mcam_init( uint8_t mcam_channel,
                                   uint8_t cam_priority,
                                   uint8_t cam_edge_polarity,
                                  uint32_t cam_angle_window_start,
                                  uint32_t cam_angle_window_width,
                                   uint8_t crank_channel,
                                   uint8_t crank_priority,
                                   uint8_t crank_edge_polarity,
                                   uint8_t crank_number_of_physical_teeth,
                                   uint8_t crank_number_of_missing_teeth,
                                   uint8_t crank_blank_tooth_count,
                                  uint32_t crank_tcr2_ticks_per_tooth,
                                ufract24_t crank_windowing_ratio_normal,
                                ufract24_t crank_windowing_ratio_after_gap,
                                ufract24_t crank_windowing_ratio_across_gap,
                                ufract24_t crank_windowing_ratio_timeout,
                                ufract24_t crank_gap_ratio,
                                  uint32_t crank_blank_time_ms,
                                  uint32_t crank_first_tooth_timeout_us,
                                  uint32_t crank_link_1,
                                  uint32_t crank_link_2,
                                  uint32_t crank_link_3,
                                  uint32_t crank_link_4,
                                  uint32_t tcr1_timebase_freq );

/* read parameter functions */
uint32_t fs_etpu_eng_pos_mcam_get_cam_edge_angle();
int8_t fs_etpu_eng_pos_mcam_get_tooth_number();
int32_t fs_etpu_eng_pos_mcam_get_tooth_time();
int32_t fs_etpu_eng_pos_mcam_get_engine_speed(uint32_t tcr1_timebase_freq);

/* read status functions */
int8_t fs_etpu_eng_pos_mcam_get_engine_position_status();
int8_t fs_etpu_eng_pos_mcam_get_cam_status();
int8_t fs_etpu_eng_pos_mcam_get_crank_status();

/* read error status functions */
int8_t fs_etpu_eng_pos_mcam_get_cam_error_status();
int8_t fs_etpu_eng_pos_mcam_get_crank_error_status();

/* clear error status functions */
int32_t fs_etpu_eng_pos_mcam_clear_cam_error_status();
int32_t fs_etpu_eng_pos_mcam_clear_crank_error_status();

/* update parameter functions */
int32_t fs_etpu_eng_pos_mcam_update_cam_window(uint32_t cam_angle_window_start,
                                               uint32_t cam_angle_window_width);

/* set windowing ratio functions */
int32_t fs_etpu_eng_pos_mcam_set_wr_normal( ufract24_t ratio );
int32_t fs_etpu_eng_pos_mcam_set_wr_after_gap( ufract24_t ratio );
int32_t fs_etpu_eng_pos_mcam_set_wr_across_gap( ufract24_t ratio );
int32_t fs_etpu_eng_pos_mcam_set_wr_timeout( ufract24_t ratio );

/* advanced functions */
int32_t fs_etpu_eng_pos_mcam_insert_tooth( uint8_t host_asserted_tooth_count );
int32_t fs_etpu_eng_pos_mcam_adjust_angle( int24_t angle_adjust );

/* debug functions */
int32_t fs_etpu_eng_pos_mcam_get_engine_cycle_0_tcr2_count();
int32_t fs_etpu_eng_pos_mcam_set_tooth_number ( uint8_t tooth_number );

/**************************************************************************
*        Information for eTPU Graphical Configuration Tool
***************************************************************************/
/* eTPU functions used: MCAM, CRANK */
/* full function name: Engine Position MCam (MCAM and CRANK channels) */
/* channel assignment; load: eng_pos_mcam
   MCAM = mcam_channel; priority=mcam_priority
   CRANK = crank_channel; priority=crank_priority
*/
/* load expression eng_pos_mcam
var engine_speed { 0..20000 } [ rpm ]

rev_360_base = 100*(engine_speed/60)/etpu_clock_freq
rev_720_base = rev_360_base/2

MCAM = (65)*rev_720_base
CRANK = (136 + (crank_number_of_physical_teeth - 2)*118 + 154)*rev_360_base
*/
