/**
 * @file   core_prv.h
 * @author sstasiak
 *
 * Copyright (c) 2013,2014 Sean Stasiak. All rights reserved.
 * Developed by: Sean Stasiak <sstasiak@gmail.com>
 * Refer to license terms in LICENSE.txt, in the absence of such a file,
 * use the following: http://creativecommons.org/licenses/by-nc/4.0/legalcode
 */

#ifndef   __core_prv_h
#define   __core_prv_h

extern unsigned long _f_handlers;     /**< linker defined                  */
extern unsigned long systime;         /**< millisec counter                */

/**
 * @internal
 * @typedef vector_fptr_t
 * @brief default interrupt handler function type
 */
typedef void(*vector_fptr_t)(void);
extern vector_fptr_t vectors[];       /**< ivor4 vector array              */
/**
 * @brief provides the option of overriding a weak ref if you want to hook
 *        into the ivor4 irq table statically
 */
void vector0( void );   void vector1( void );   void vector2( void );
void vector3( void );   void vector4( void );   void vector5( void );
void vector6( void );   void vector7( void );   void vector8( void );
void vector9( void );   void vector10( void );  void vector11( void );
void vector12( void );  void vector13( void );  void vector14( void );
void vector15( void );  void vector16( void );  void vector17( void );
void vector18( void );  void vector19( void );  void vector20( void );
void vector21( void );  void vector22( void );  void vector23( void );
void vector24( void );  void vector25( void );  void vector26( void );
void vector27( void );  void vector28( void );  void vector29( void );
void vector30( void );  void vector31( void );  void vector32( void );
void vector33( void );  void vector34( void );  void vector35( void );
void vector36( void );  void vector37( void );  void vector38( void );
void vector39( void );  void vector40( void );  void vector41( void );
void vector42( void );  void vector43( void );  void vector44( void );
void vector45( void );  void vector46( void );  void vector47( void );
void vector48( void );  void vector49( void );  void vector50( void );
void vector51( void );  void vector52( void );  void vector53( void );
void vector54( void );  void vector55( void );  void vector56( void );
void vector57( void );  void vector58( void );  void vector59( void );
void vector60( void );  void vector61( void );  void vector62( void );
void vector63( void );  void vector64( void );  void vector65( void );
void vector66( void );  void vector67( void );  void vector68( void );
void vector69( void );  void vector70( void );  void vector71( void );
void vector72( void );  void vector73( void );  void vector74( void );
void vector75( void );  void vector76( void );  void vector77( void );
void vector78( void );  void vector79( void );  void vector80( void );
void vector81( void );  void vector82( void );  void vector83( void );
void vector84( void );  void vector85( void );  void vector86( void );
void vector87( void );  void vector88( void );  void vector89( void );
void vector90( void );  void vector91( void );  void vector92( void );
void vector93( void );  void vector94( void );  void vector95( void );
void vector96( void );  void vector97( void );  void vector98( void );
void vector99( void );  void vector100( void ); void vector101( void );
void vector102( void ); void vector103( void ); void vector104( void );
void vector105( void ); void vector106( void ); void vector107( void );
void vector108( void ); void vector109( void ); void vector110( void );
void vector111( void ); void vector112( void ); void vector113( void );
void vector114( void ); void vector115( void ); void vector116( void );
void vector117( void ); void vector118( void ); void vector119( void );
void vector120( void ); void vector121( void ); void vector122( void );
void vector123( void ); void vector124( void ); void vector125( void );
void vector126( void ); void vector127( void ); void vector128( void );
void vector129( void ); void vector130( void ); void vector131( void );
void vector132( void ); void vector133( void ); void vector134( void );
void vector135( void ); void vector136( void ); void vector137( void );
void vector138( void ); void vector139( void ); void vector140( void );
void vector141( void ); void vector142( void ); void vector143( void );
void vector144( void ); void vector145( void ); void vector146( void );
void vector147( void ); void vector148( void ); void vector149( void );
void vector150( void ); void vector151( void ); void vector152( void );
void vector153( void ); void vector154( void ); void vector155( void );
void vector156( void ); void vector157( void ); void vector158( void );
void vector159( void ); void vector160( void ); void vector161( void );
void vector162( void ); void vector163( void ); void vector164( void );
void vector165( void ); void vector166( void ); void vector167( void );
void vector168( void ); void vector169( void ); void vector170( void );
void vector171( void ); void vector172( void ); void vector173( void );
void vector174( void ); void vector175( void ); void vector176( void );
void vector177( void ); void vector178( void ); void vector179( void );
void vector180( void ); void vector181( void ); void vector182( void );
void vector183( void ); void vector184( void ); void vector185( void );
void vector186( void ); void vector187( void ); void vector188( void );
void vector189( void ); void vector190( void ); void vector191( void );
void vector192( void ); void vector193( void ); void vector194( void );
void vector195( void ); void vector196( void ); void vector197( void );
void vector198( void ); void vector199( void ); void vector200( void );
void vector201( void ); void vector202( void ); void vector203( void );
void vector204( void ); void vector205( void ); void vector206( void );
void vector207( void ); void vector208( void ); void vector209( void );
void vector210( void ); void vector211( void ); void vector212( void );
void vector213( void ); void vector214( void ); void vector215( void );
void vector216( void ); void vector217( void ); void vector218( void );
void vector219( void ); void vector220( void ); void vector221( void );
void vector222( void ); void vector223( void ); void vector224( void );
void vector225( void ); void vector226( void ); void vector227( void );
void vector228( void ); void vector229( void ); void vector230( void );
void vector231( void ); void vector232( void ); void vector233( void );
void vector234( void ); void vector235( void ); void vector236( void );
void vector237( void ); void vector238( void ); void vector239( void );
void vector240( void ); void vector241( void ); void vector242( void );
void vector243( void ); void vector244( void ); void vector245( void );
void vector246( void ); void vector247( void ); void vector248( void );
void vector249( void ); void vector250( void ); void vector251( void );
void vector252( void ); void vector253( void ); void vector254( void );
void vector255( void ); void vector256( void ); void vector257( void );
void vector258( void ); void vector259( void ); void vector260( void );
void vector261( void ); void vector262( void ); void vector263( void );
void vector264( void ); void vector265( void ); void vector266( void );
void vector267( void ); void vector268( void ); void vector269( void );
void vector270( void ); void vector271( void ); void vector272( void );
void vector273( void ); void vector274( void ); void vector275( void );
void vector276( void ); void vector277( void ); void vector278( void );
void vector279( void ); void vector280( void ); void vector281( void );
void vector282( void ); void vector283( void ); void vector284( void );
void vector285( void ); void vector286( void ); void vector287( void );
void vector288( void ); void vector289( void ); void vector290( void );
void vector291( void ); void vector292( void ); void vector293( void );
void vector294( void ); void vector295( void ); void vector296( void );
void vector297( void ); void vector298( void ); void vector299( void );
void vector300( void ); void vector301( void ); void vector302( void );
void vector303( void ); void vector304( void ); void vector305( void );
void vector306( void ); void vector307( void ); void vector308( void );
void vector309( void ); void vector310( void ); void vector311( void );
void vector312( void ); void vector313( void ); void vector314( void );
void vector315( void ); void vector316( void ); void vector317( void );
void vector318( void ); void vector319( void ); void vector320( void );
void vector321( void ); void vector322( void ); void vector323( void );
void vector324( void ); void vector325( void ); void vector326( void );
void vector327( void ); void vector328( void ); void vector329( void );
void vector330( void ); void vector331( void ); void vector332( void );
void vector333( void ); void vector334( void ); void vector335( void );
void vector336( void ); void vector337( void ); void vector338( void );
void vector339( void ); void vector340( void ); void vector341( void );
void vector342( void ); void vector343( void ); void vector344( void );
void vector345( void ); void vector346( void ); void vector347( void );
void vector348( void ); void vector349( void ); void vector350( void );
void vector351( void ); void vector352( void ); void vector353( void );
void vector354( void ); void vector355( void ); void vector356( void );
void vector357( void ); void vector358( void ); void vector359( void );
void vector360( void ); void vector361( void ); void vector362( void );
void vector363( void ); void vector_default( void );

/**
 * @brief default ivor0 handler, override as desired
 * @note Critical input (SPR 400)
 */
void
  ivor0_handler( void );

/**
 * @brief default ivor1 handler, override as desired
 * @note Machine check interrupt (SPR 401)
 */
void
  ivor1_handler( void );

/**
 * @brief default ivor2 handler, override as desired
 * @note Data storage interrupt (SPR 402)
 */
void
  ivor2_handler( void );

/**
 * @brief default ivor3 handler, override as desired
 * @note Instruction storage interrupt (SPR 403)
 */
void
  ivor3_handler( void );

/**
 * @brief default ivor4 handler, override as desired
 * @note  External input interrupt (SPR 404)
 */
void
  ivor4_handler( void );

/**
 * @brief default ivor5 handler, override as desired
 * @note Alignment interrupt (SPR 405)
 */
void
  ivor5_handler( void );

/**
 * @brief default ivor6 handler, override as desired
 * @note Program interrupt (SPR 406)
 */
void
  ivor6_handler( void );

/**
 * @brief default ivor7 handler, override as desired
 * @note Floating-point unavailable interrupt (SPR 407)
 */
void
  ivor7_handler( void );

/**
 * @brief default ivor8 handler, override as desired
 * @note System call interrupt (SPR 408)
 */
void
  ivor8_handler( void );

/**
 * @brief default ivor9 handler, override as desired
 * @note Auxiliary processor (SPR 409)
 */
void
  ivor9_handler( void );

/**
 * @brief default ivor10 handler, override as desired
 * @note Decrementer interrupt (SPR 410)
 */
void
  ivor10_handler( void );

/**
 * @brief default ivor11 handler, override as desired
 * @note Fixed-interval timer interrupt (SPR 411)
 */
void
  ivor11_handler( void );

/**
 * @brief default ivor12 handler, override as desired
 * @note Watchdog timer interrupt (SPR 412)
 */
void
  ivor12_handler( void );

/**
 * @brief default ivor13 handler, override as desired
 * @note Data TLB error interrupt (SPR 413)
 */
void
  ivor13_handler( void );

/**
 * @brief default ivor14 handler, override as desired
 * @note Instruction TLB error interrupt (SPR 414)
 */
void
  ivor14_handler( void );

/**
 * @brief default ivor15 handler, override as desired
 * @note Debug interrupt (SPR 415)
 */
void
  ivor15_handler( void );

/**
 * @brief default ivor32 handler, override as desired
 * @note SPE APU unavailable interrupt (SPR 528)
 */
void
  ivor32_handler( void );

/**
 * @brief default ivor33 handler, override as desired
 * @note SPE floating-point data exception interrupt (SPR 529)
 */
void
  ivor33_handler( void );

/**
 * @brief default ivor34 handler, override as desired
 * @note SPE floating-point round exception interrupt (SPR 530)
 */
void
  ivor34_handler( void );

/**
 * @brief tick handler called from ivor10
 */
extern void (*tick_handler)(void);

/**
 * @brief setup default dma groupings and priorities
 */
void
  edma_init( void );

/**
 * @brief register an individual dma error callback
 */
typedef void (*edma_err_cb_t)(unsigned esr);
void
  edma_reg_errhnd( unsigned channel,
                   edma_err_cb_t cb );

#endif // __core_prv_h
