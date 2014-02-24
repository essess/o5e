/**
 * @file   err.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __err_h
#define   __err_h

#include <stdint.h>

/**
 * [ 4bits ][   6bits   ][    6bits     ]
 * [  0000 ][ module_id ][   code_id    ]
 */

#define RESERVED_MODULE         (  0 )    /**< NOT available for use */
#define MISC_MODULE             (  1 )
#define UTIL_MODULE             (  2 )
#define TUNER_MODULE            (  3 )
#define SERIAL_MODULE           (  4 )
#define CAL_MODULE              (  5 )
#define ETPU_MODULE             (  6 )
#define ENGPOS_MODULE           (  7 )
#define ANA_MODULE              (  9 )
#define TANA_MODULE             ( 10 )
#define TTOOTHGEN_MODULE        ( 11 )

#define _CODE( mod_, code_ )    ( ((mod_&0x3ful) << 6) | (code_&0x3ful) )

#define MISC_CODE( code_ )      ( _CODE( MISC_MODULE, code_ ) )
#define UTIL_CODE( code_ )      ( _CODE( UTIL_MODULE, code_ ) )
#define TUNER_CODE( code_ )     ( _CODE( TUNER_MODULE, code_ ) )
#define SERIAL_CODE( code_ )    ( _CODE( SERIAL_MODULE, code_ ) )
#define CAL_CODE( code_ )       ( _CODE( CAL_MODULE, code_ ) )
#define ETPU_CODE( code_ )      ( _CODE( ETPU_MODULE, code_ ) )
#define ENGPOS_CODE( code_ )    ( _CODE( ENGPOS_MODULE, code_ ) )
#define ANA_CODE( code_ )       ( _CODE( ANA_MODULE, code_ ) )
#define TANA_CODE( code_ )      ( _CODE( TANA_MODULE, code_ ) )
#define TTOOTHGEN_CODE( code_ ) ( _CODE( TTOOTHGEN_MODULE, code_ ) )

#define GET_MODULE( code_ )     ( (code_ & (0x3fu<<6)) >> 6 )
#define GET_CODE( code_ )       ( code_ & 0x3fu )

/**
 * @public all error codes originate here:
 */
enum
{
  CODE_NONE = 0,

  CODE_MISC_NOCAL           = MISC_CODE(  0 ),
  CODE_MISC_TESTMODE        = MISC_CODE(  1 ),
  CODE_MISC_CALBLK          = MISC_CODE(  2 ),
  CODE_MISC_GSUPOT          = MISC_CODE(  3 ),
  CODE_MISC_GSRPM           = MISC_CODE(  4 ),
  CODE_MISC_GSUMAP          = MISC_CODE(  5 ),
  CODE_MISC_GSUCLT          = MISC_CODE(  6 ),
  CODE_MISC_GSUMAT          = MISC_CODE(  7 ),
  CODE_MISC_GSUTPS          = MISC_CODE(  8 ),
  CODE_MISC_GSUM1           = MISC_CODE(  9 ),
  CODE_MISC_GSUM2           = MISC_CODE( 10 ),
  CODE_MISC_GSUM3           = MISC_CODE( 11 ),
  CODE_MISC_GSUM4           = MISC_CODE( 12 ),
  CODE_MISC_GSUM5           = MISC_CODE( 13 ),
  CODE_MISC_GSUUCTEMP       = MISC_CODE( 14 ),

  CODE_UTIL_BCSRCPTR        = UTIL_CODE(  0 ),
  CODE_UTIL_BCDSTPTR        = UTIL_CODE(  1 ),
  CODE_UTIL_WCSRCPTR        = UTIL_CODE(  2 ),
  CODE_UTIL_WCDSTPTR        = UTIL_CODE(  3 ),
  CODE_UTIL_WCSRCPTRALIGN   = UTIL_CODE(  4 ),
  CODE_UTIL_WCDSTPTRALIGN   = UTIL_CODE(  5 ),
  CODE_UTIL_WCCNTMODSIZE    = UTIL_CODE(  6 ),
  CODE_UTIL_CRCBUFFPTR      = UTIL_CODE(  7 ),
  CODE_UTIL_BFDSTPTR        = UTIL_CODE(  8 ),
  CODE_UTIL_WFDSTPTR        = UTIL_CODE(  9 ),
  CODE_UTIL_WFDSTPTRALIGN   = UTIL_CODE( 10 ),
  CODE_UTIL_WFCNTMODSIZE    = UTIL_CODE( 11 ),

  CODE_TUNER_TTNOSERIAL     = TUNER_CODE(  0 ),
  CODE_TUNER_TTUNKCMD       = TUNER_CODE(  1 ),
  CODE_TUNER_TTUNHCMD       = TUNER_CODE(  2 ),
  CODE_TUNER_TCTID          = TUNER_CODE(  3 ),
  CODE_TUNER_TTCRC          = TUNER_CODE(  4 ),
  CODE_TUNER_TTDATALEN      = TUNER_CODE(  5 ),
  CODE_TUNER_TTCC           = TUNER_CODE(  6 ),
  CODE_TUNER_TTCOMMITFAIL   = TUNER_CODE(  7 ),
  CODE_TUNER_TTPGCBPBO      = TUNER_CODE(  8 ),
  CODE_TUNER_PPPTR          = TUNER_CODE(  9 ),
  CODE_TUNER_PPCMD          = TUNER_CODE( 10 ),
  CODE_TUNER_PPLEN          = TUNER_CODE( 11 ),
  CODE_TUNER_PUPTR          = TUNER_CODE( 12 ),
  CODE_TUNER_PULEN          = TUNER_CODE( 13 ),
  CODE_TUNER_PAPTR          = TUNER_CODE( 14 ),
  CODE_TUNER_PACMD          = TUNER_CODE( 15 ),
  CODE_TUNER_PALEN          = TUNER_CODE( 16 ),
  CODE_TUNER_PQPTR          = TUNER_CODE( 17 ),
  CODE_TUNER_PQCMD          = TUNER_CODE( 18 ),
  CODE_TUNER_PQLEN          = TUNER_CODE( 19 ),
  CODE_TUNER_PSPTR          = TUNER_CODE( 20 ),
  CODE_TUNER_PSCMD          = TUNER_CODE( 21 ),
  CODE_TUNER_PSLEN          = TUNER_CODE( 22 ),
  CODE_TUNER_PWPTR          = TUNER_CODE( 23 ),
  CODE_TUNER_PWCMD          = TUNER_CODE( 24 ),
  CODE_TUNER_PWLEN          = TUNER_CODE( 25 ),
  CODE_TUNER_PRPTR          = TUNER_CODE( 26 ),
  CODE_TUNER_PRCMD          = TUNER_CODE( 27 ),
  CODE_TUNER_PRLEN          = TUNER_CODE( 28 ),
  CODE_TUNER_PKPTR          = TUNER_CODE( 29 ),
  CODE_TUNER_PKCMD          = TUNER_CODE( 30 ),
  CODE_TUNER_PKLEN          = TUNER_CODE( 31 ),
  CODE_TUNER_PKRANGE        = TUNER_CODE( 32 ),
  CODE_TUNER_PRRANGE        = TUNER_CODE( 33 ),
  CODE_TUNER_PWRANGE        = TUNER_CODE( 34 ),

  CODE_SERIAL_SGPTR         = SERIAL_CODE(  0 ),
  CODE_SERIAL_SGSIZE        = SERIAL_CODE(  1 ),
  CODE_SERIAL_SVOVERRUN     = SERIAL_CODE(  2 ),
  CODE_SERIAL_SVNOISE       = SERIAL_CODE(  3 ),
  CODE_SERIAL_SVFRAMING     = SERIAL_CODE(  4 ),
  CODE_SERIAL_SVPARITY      = SERIAL_CODE(  5 ),
  CODE_SERIAL_SVRXFULL      = SERIAL_CODE(  6 ),
  CODE_SERIAL_SRBPTR        = SERIAL_CODE(  7 ),
  CODE_SERIAL_SRBTIE        = SERIAL_CODE(  8 ),
  CODE_SERIAL_SRBRIE        = SERIAL_CODE(  9 ),
  CODE_SERIAL_SRPTR         = SERIAL_CODE( 10 ),
  CODE_SERIAL_SREPTR        = SERIAL_CODE( 11 ),
  CODE_SERIAL_SSBPTR        = SERIAL_CODE( 12 ),
  CODE_SERIAL_SSBTIE        = SERIAL_CODE( 13 ),
  CODE_SERIAL_SSBRIE        = SERIAL_CODE( 14 ),
  CODE_SERIAL_SSPTR         = SERIAL_CODE( 15 ),
  CODE_SERIAL_SSEPTR        = SERIAL_CODE( 16 ),

  CODE_CAL_CIFPTR           = CAL_CODE(  0 ),
  CODE_CAL_CLTOOSMALL       = CAL_CODE(  1 ),
  CODE_CAL_CTLSWAP          = CAL_CODE(  2 ),
  CODE_CAL_CCEB             = CAL_CODE(  3 ),
  CODE_CAL_CCSWAP           = CAL_CODE(  4 ),
  CODE_CAL_CCCFEE           = CAL_CODE(  5 ),
  CODE_CAL_CCCEFWB          = CAL_CODE(  6 ),
  CODE_CAL_CCCEFW           = CAL_CODE(  7 ),
  CODE_CAL_CCCEFWE          = CAL_CODE(  8 ),
  CODE_CAL_CCCECRCCHK       = CAL_CODE(  9 ),
  CODE_CAL_CCCEINVALIDATE   = CAL_CODE( 10 ),
  CODE_CAL_CCCEVALIDATE     = CAL_CODE( 11 ),
  CODE_CAL_CCCEBADWS        = CAL_CODE( 12 ),
  CODE_CAL_CCE              = CAL_CODE( 13 ),


  CODE_ETPU_INIT            = ETPU_CODE(  0 ),
  CODE_ETPU_INIT2           = ETPU_CODE(  1 ),

  CODE_ENGPOS_CREATE        = ENGPOS_CODE(  0 ),
  CODE_ENGPOS_EPMINIT       = ENGPOS_CODE(  1 ),
  CODE_ENGPOS_CIS0MI        = ENGPOS_CODE(  2 ),
  CODE_ENGPOS_CIS1MI        = ENGPOS_CODE(  3 ),

  CODE_ANA_GETSRC           = ANA_CODE(  0 ),
  CODE_ANA_INITRATE         = ANA_CODE(  1 ),
  CODE_ANA_REINIT           = ANA_CODE(  2 ),
  CODE_ANA_INITPF           = ANA_CODE(  3 ),
  CODE_ANA_UNKERR           = ANA_CODE(  4 ),

  CODE_TANA_CREATETID       = TANA_CODE(  0 ),
  CODE_TANA_SPTRSEM         = TANA_CODE(  1 ),
  CODE_TANA_ERRCFIFO        = TANA_CODE(  2 ),
  CODE_TANA_ERRRFIFO        = TANA_CODE(  3 ),
  CODE_TANA_UNKEVT          = TANA_CODE(  4 ),


  CODE_TTOOTHGEN_CREATE     = TTOOTHGEN_CODE(  0 ),
  CODE_TTOOTHGEN_TGMODE     = TTOOTHGEN_CODE(  1 ),
  CODE_TTOOTHGEN_TGINIT     = TTOOTHGEN_CODE(  2 ),
  CODE_TTOOTHGEN_TFIXADJ    = TTOOTHGEN_CODE(  3 ),
  CODE_TTOOTHGEN_TFIXMODE   = TTOOTHGEN_CODE(  4 ),
  CODE_TTOOTHGEN_TJITMODE   = TTOOTHGEN_CODE(  5 ),
  CODE_TTOOTHGEN_TJITPADJ   = TTOOTHGEN_CODE(  6 ),
  CODE_TTOOTHGEN_TJITMADJ   = TTOOTHGEN_CODE(  7 ),
  CODE_TTOOTHGEN_TCYCMODE   = TTOOTHGEN_CODE(  8 ),
  CODE_TTOOTHGEN_TCYC0ADJ   = TTOOTHGEN_CODE(  9 ),
  CODE_TTOOTHGEN_TCYC1ADJ   = TTOOTHGEN_CODE( 10 ),
  CODE_TTOOTHGEN_TCYC2ADJ   = TTOOTHGEN_CODE( 11 ),
  CODE_TTOOTHGEN_TCYC3ADJ   = TTOOTHGEN_CODE( 12 ),

};

/**
 * @public
 * @brief use the following as a logging assert mechanism
 *        without the side effect of locking up the core
 * @note this should be used just about everywhere EXCEPT
 *       for the err api and its dependencies. use of real
 *       trap()'s (blocking) should be avoided in this codebase
 */
#ifndef NDEBUG
  #define err_assert(exp_,code_) \
    do { if (!(exp_)) { err_push(code_); } } while(0)
#else
  #define err_assert(exp_,code_) \
    do { (void)sizeof(exp_); (void)sizeof(code_); } while(0)
#endif

#define ERR_DEPTH (16) /**< depth of code FIFO stack */
typedef struct err_t err_t; /**< fwd decl */

/**
 * @public
 * @typedef err_notifier_t
 * @brief notifier callback
 */
typedef void (err_cb_t)(uint32_t code);

/**
 * @public
 * @brief init code logger
 * @param[in] fptr function called when a code is pushed, CODE_NONE passed
 *                 along when everything has been popped off the stack
 * @retval none
 * @note { not threadsafe }
 */
void
  err_init( err_cb_t *fptr );

/**
 * @public
 * @brief push an error code into the stack
 * @param[in] code error code
 * @retval none
 * @note { threadsafe }
 */
void
  err_push( uint32_t code );

/**
 * @public
 * @brief nondestructively return the topmost error if present
 * @param none
 * @retval uint32_t err code or CODE_NONE
 * @note { threadsafe (but expensive) }
 */
uint32_t
  err_peek( void );

/**
 * @public
 * @brief pop oldest error from the stack
 * @param none
 * @retval err_t* err or 0 if none
 * @note { threadsafe }
 */
err_t const *
  err_pop( void );

/**
 * @public
 * @brief extract timestamp from err
 * @param[in] e err
 * @retval uint64_t timestamp
 */
uint64_t
  err_get_ts( err_t const *e );

/**
 * @public
 * @brief extract err code from err
 * @param[in] e err
 * @retval uint32_t code
 */
uint32_t
  err_get_code( err_t const *e );

/**
 * @public
 * @brief return err_t back to the free pool
 * @param[in] e previously pop'd err
 * @retval none
 * @note { threadsafe }
 */
void
  err_destroy( err_t const *e );

#endif // __err_h
