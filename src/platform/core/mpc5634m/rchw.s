#
# @file       rchw.s
# @headerfile rchw.inc
# @author     sean
# @brief      reset configuration halfword
#
# Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
# Developed by: Sean Stasiak <sstasiak@gmail.com>
# Refer to license terms in LICENSE.txt, in the absence of such a file,
# use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
#

    .include    "platform/core/mpc5634m/rchw.inc"
    .extern     cstart        # hard reset entry point

#----------------------------------------------------------
#
#   BAM reset configuration halfword definition:
#

SWT_OPT     .equ    SWT_OFF
WTE_OPT     .equ    WTE_OFF
PS0_OPT     .equ    0         # reserved in mpc5634m
VLE_OPT     .equ    VLE_OFF

    .section    .rchw, rodata

    .long       BOOT_ID | SWT_OPT | WTE_OPT | PS0_OPT | VLE_OPT
    .long       cstart
