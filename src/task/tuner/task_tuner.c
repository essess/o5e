/**
 * @file       task_tuner.c
 * @headerfile task_tuner_prv.h
 * @author     sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#include "task/tuner/task_tuner_prv.h"
#include "cocoos.h"
#include "cal.h"
#include "util.h"
#include "err.h"
#include "serial.h"
#include "led.h"

/* size of a min logical '001' style packet:                               */
#define SIZEOF_MINPKT (sizeof(uint16_t)+sizeof(uint8_t)+sizeof(uint32_t))
/*                              len    +  cmd char     +   crc             */

/* --| TYPES    |--------------------------------------------------------- */
/* --| STATICS  |--------------------------------------------------------- */
/* --| INLINES  |--------------------------------------------------------- */
/* --| PUBLIC   |--------------------------------------------------------- */
/* --| INTERNAL |--------------------------------------------------------- */

/**
 * @internal
 * @brief tuner studio i/o task
 */
void
  task_tuner( void )
{
  task_open();
  static uint8_t buffer[SERBUFF_BYTESIZE];
  static serial_t *pserial;
  pserial = serial_get( buffer, SERBUFF_BYTESIZE );
  while( pserial )
  {
    /* We're following megasquirt style half-duplex slave comms to leverage  */
    /* Tuner Studio [http://tunerstudio.com/] for calibration manipulation.  */
    serial_recv_begin( pserial );
    /* wait for something to roll in ... */
    static uint32_t cnt;
    do
    {
      task_wait( 5 );    /**< 1024 bytes good for about 14ms @ 115,200 */
      cnt = serial_recv( pserial );
    }
    while( !cnt );
    /* capture the rest ... megasquirt style comms depends on a pause to sync */
    /* the stream                                                             */
    static uint32_t idlecnt;
    static uint32_t prev_cnt;
    idlecnt = 0; /**< reset counter from last go round */
    do
    {
      task_wait( 5 );
      prev_cnt = cnt;
      cnt = serial_recv( pserial );
      if( prev_cnt == cnt )
        idlecnt++;
      else
        idlecnt = 0;  /**< reset on arrival of bytes */
    }
    while( idlecnt < 6 ); /**< >=6 (30+ms) is the magic 'stable' number */
    serial_recv_end( pserial );
    /* process and craft a response using passed buffer. sadly, because we */
    /* can't tolerate any blocking and cocoos is non-preemptive, we can't  */
    /* 'break out' the processing of some commands (burn specifically) so  */
    /* that we can get access to cocoos calls that yield the cpu.          */
    /* ... not elegant; nor pretty, but such is the world of compromises   */
    if( cnt >= SIZEOF_MINPKT )
    {
      /* try for an '001' style packet: */
      static uint16_t *const pdatalen = (uint16_t*)buffer;
      if( (*pdatalen != 0) && (*pdatalen < SERBUFF_BYTESIZE) )
      {
        /* reset pointers: */
        static uint8_t *const pdata = (uint8_t*)&buffer[2];
        static uint32_t *ppktcrc;
        ppktcrc = (uint32_t*)&pdata[*pdatalen];

        /* check crc: */
        static uint32_t crc;
        crc = crc32(0, pdata, *pdatalen);
        if( crc != *ppktcrc )
        {
          /* bad CRC (0x82) pre-computed response: */
          static uint8_t const bad_crc[] = { 0x00,0x01,BAD_CRC,0xd1,0xb4,0x0d,0x81 };
          cnt = sizeof( bad_crc );
          bytecpy( buffer, bad_crc, cnt );
          err_push( CODE_TUNER_TTCRC );
        }
        else
        {
          /* burn special case?: */
          if( *pdata == 'b' )
          {
            /* note: in the future, if any autotune algs are implemented and */
            /*       write to cal space, those will have to be halted during */
            /*       this operation - cal space must be untouched so that crc*/
            /*       calcs can be performed correctly                        */
            *pdatalen = sizeof(uint8_t);
            *pdata = SEQUENCE_FAILURE_2;
            /* idle->erase->write->idle ~700ms */
            led_on( LED_FLASH_BUSY );
            if( cal_commit() == CCS_ERASE )
            { /* kickoff: */
              do { /* wait erase: */
                task_wait( 5 );
              } while( cal_commit_chk() == CCS_ERASE );
              do { /* wait write: */
                OS_SCHEDULE;
              } while( cal_commit_chk() == CCS_WRITE );
              if( cal_commit_chk() == CCS_IDLE )
                *pdata = OK;
              else
                err_push( CODE_TUNER_TTCOMMITFAIL );
            }
            else
              err_push( CODE_TUNER_TTCC );
            led_off( LED_FLASH_BUSY );
          }
          else
          {
            static uint16_t (*pprocess_func)( uint8_t*, uint16_t );
            switch( *pdata )
            {
              case 'A':
                pprocess_func = process_A;
                break;
              case 'w':
                pprocess_func = process_w;
                break;
              case 'r':
                pprocess_func = process_r;
                break;
              case 'k':
                pprocess_func = process_k;
                break;
              case 'Q':
                pprocess_func = process_Q;
                break;
              case 'S':
                pprocess_func = process_S;
                break;
              default:
                pprocess_func = process_unh;
                err_push( CODE_TUNER_TTUNHCMD );
            }
            *pdatalen = pprocess_func( pdata, *pdatalen );
          }
          OS_SCHEDULE;  /**< in case a big bytecpy occured  ...   */
          ppktcrc = (uint32_t*)&pdata[*pdatalen];
          *ppktcrc = crc32( 0, pdata, *pdatalen );
          OS_SCHEDULE;  /**< ... a big crc is also going to occur */
          cnt = sizeof(*pdatalen) + *pdatalen + sizeof(*ppktcrc);
        }
      }
      else
      {
        err_push( CODE_TUNER_TTDATALEN );
        cnt = 0;
      }
    }
    else
    { /* try the single char stuff: */
      switch( buffer[0] )
      {
        case 'F':
          /* support ms 'envelope' style comms */
          static uint8_t const f_reply[] = { '0','0','1' };
          cnt = sizeof( f_reply );
          bytecpy( buffer, f_reply, cnt );
          break;
        case 'p':
          /* pop error code */
          cnt = process_p( buffer, sizeof(buffer[0]) );
          break;
        default:
          err_push( CODE_TUNER_TTUNKCMD );
          cnt = 0;
      }
    }
    /* send back response (if present): */
    if( cnt )
    {
      serial_send_begin( pserial, cnt );
      while( serial_send(pserial) )
        task_wait( 1 );
      serial_send_end( pserial );
    }
  }
  err_push( CODE_TUNER_TTNOSERIAL );
  task_close();
}
