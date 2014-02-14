/**
 * @file   calblk.h
 * @author sstasiak
 * @brief  calibration block 'overlay'
 *
 * Copyright (c) 2013, 2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __calblk_h
#define   __calblk_h

#include <stdint.h>

typedef struct
{
  struct
  {
    struct
    {
      uint32_t           :22;       // [10:31] /**< @ 0x0000 - 0    */
      uint32_t     mteeth:2;        // [8:9]
      uint32_t crank_edge:1;        // [7:7]
      uint32_t   cam_edge:1;        // [6:6]
      uint32_t           :5;        // [1:5]
      uint32_t       type:1;        // [0:0]
    };
    struct
    {
      uint32_t     teeth:8;         // [U08]  /**< @ 0x0004 - 4    */
      uint32_t blanktcnt:8;         // [U08]  /**< @ 0x0005 - 5    */
      uint32_t blankt_ms:16;        // [U16]  /**< @ 0x0006 - 6    */
    };
    uint32_t ftto;                            /**< @ 0x0008 - 8    */
    struct
    {
      uint32_t   camstart:16;       // [U16]  /**< @ 0x000c - 12   */
      uint32_t      width:16;       // [U16]  /**< @ 0x000e - 14   */
    } defw;
    struct
    {
      uint32_t norm;                          /**< @ 0x0010 - 16   */
      uint32_t aftergap;                      /**< @ 0x0014 - 20   */
      uint32_t acrossgap;                     /**< @ 0x0018 - 24   */
      uint32_t timeout;                       /**< @ 0x001c - 28   */
    } defwr;
  } cccfg;

  uint8_t skip0[1584];

  struct
  {
    struct
    {
      uint32_t          :29;        // [3:31] /**< @ 0x0650 - 1616 */
      uint32_t   tg_mode:2;         // [1:2]
      uint32_t    enable:1;         // [0:0]
    };
    uint16_t pot;                             /**< @ 0x0654 - 1620 */
    uint16_t map;                             /**< @ 0x0656 - 1622 */
    uint16_t clt;                             /**< @ 0x0658 - 1624 */
    uint16_t mat;                             /**< @ 0x065a - 1626 */
    uint16_t tps;                             /**< @ 0x065c - 1628 */
    uint16_t m1;                              /**< @ 0x065e - 1630 */
    uint16_t m2;                              /**< @ 0x0660 - 1632 */
    uint16_t m3;                              /**< @ 0x0662 - 1634 */
    uint16_t m4;                              /**< @ 0x0664 - 1636 */
    uint16_t m5;                              /**< @ 0x0666 - 1638 */
    uint16_t rpm;                             /**< @ 0x0668 - 1640 */
    struct
    {
      uint16_t      tcnt:8;         // [U08]  /**< @ 0x066a - 1642 */
      uint16_t     mtcnt:8;         // [U08]  /**< @ 0x066b - 1643 */
    };
    struct
    {
      uint32_t   ctstart:8;         // [U08]  /**< @ 0x066c - 1644 */
      uint32_t    ctstop:8;         // [U08]  /**< @ 0x066d - 1645 */
      uint32_t     accel:8;         // [U08]  /**< @ 0x066e - 1646 */
      uint32_t     tg_dc:8;         // [U08]  /**< @ 0x066f - 1647 */
    };
    struct
    {
      uint16_t    jdwell:8;         // [U08]  /**< @ 0x0670 - 1648 */
      uint16_t    jrange:8;         // [U08]  /**< @ 0x0671 - 1649 */
    };
    uint16_t cdwell0;                         /**< @ 0x0672 - 1650 */
    uint16_t cdwell1;                         /**< @ 0x0674 - 1652 */
    uint16_t cdwell2;                         /**< @ 0x0676 - 1654 */
    uint16_t cdwell3;                         /**< @ 0x0678 - 1656 */
    uint16_t crpm0;                           /**< @ 0x067a - 1658 */
    uint16_t crpm1;                           /**< @ 0x067c - 1660 */
    uint16_t crpm2;                           /**< @ 0x067e - 1662 */
    uint16_t crpm3;                           /**< @ 0x0680 - 1664 */
    struct
    {
      uint16_t   caccel0:8;         // [U08]  /**< @ 0x0682 - 1666 */
      uint16_t   caccel1:8;         // [U08]  /**< @ 0x0683 - 1667 */
    };
    struct
    {
      uint32_t   caccel2:8;         // [U08]  /**< @ 0x0684 - 1668 */
      uint32_t   caccel3:8;         // [U08]  /**< @ 0x0685 - 1669 */
      uint32_t          :8;         // [U08]  /**< @ 0x0686 - 1670 */
      uint32_t          :8;         // [U08]  /**< @ 0x0687 - 1671 */
    };
  } test;
} calblk_t;

/* calblk.cccfg.type: */
#define CCCFG_TYPE_FREESCALE  (0)

/* calblk.test.tg_mode: */
#define TGMODE_FIXED    (0)
#define TGMODE_JITTER   (1)
#define TGMODE_CYCLE    (2)

#endif // __calblk_h