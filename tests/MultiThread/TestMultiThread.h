#include <testngpp/testngpp.hpp>
#include <trans-dsl/TransactionDSL.h>
#include "event/impl/SimpleEventInfo.h"
#include "event/concept/Event.h"

using namespace cub;
using namespace tsl;
using namespace ev;

namespace cub
{
  extern void log_error(const char* file, unsigned int line, const char* fmt, ...)
  {
  }
}

enum : Status
{
    ERROR1 = failStatus(200),
    ERROR2,
    ERROR3,
    ERROR4,
    E_CANCELED,
    E_REESTAB
};


struct MyContext : private SimpleRuntimeContext, SimpleTransactionContext
{
   MyContext() : SimpleTransactionContext((RuntimeContext&)*this)
   {
   }
};


FIXTURE(mt1)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __wait(1))
       , __wait(2)
       , __join(1)
       , __wait(3))
   ) trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   // @test(id="event-1")
   TEST("after recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(1)));
   }

   // @test(id="event-2")
   TEST("after recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(2)));
   }

   // @test(id="event-1-2", depends="event-1")
   TEST("after recv event-1, if recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(2)));
   }

   // @test(id="event-2-1", depends="event-2")
   TEST("after recv event-2, if recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(1)));
   }

   // @test(depends="event-1-2")
   TEST("after recv event-1-2, if recv event-3, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(depends="event-2-1")
   TEST("after recv event-2-1, if recv event-3, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(depends="event-2")
   TEST("after recv event-2, if recv event-3, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(3)));
   }
};

FIXTURE(mt2)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __sequential(__wait(1), __throw(ERROR1)))
       , __join(1)
       , __wait(2))
   ) trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   TEST("after recv event-1, should return ERROR1")
   {
      ASSERT_EQ(ERROR1, trans.handleEvent(SimpleEventInfo(1)));
   }

   TEST("after recv event-2, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(2)));
   }
};

FIXTURE(mt3)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __wait(1))
       , __fork(2, __wait(2))
       , __join(1, 2)
       , __wait(3))
   ) trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   // @test(id="event-1")
   TEST("after recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(1)));
   }

   // @test(id="event-2")
   TEST("after recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(2)));
   }

   TEST("after recv event-3, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(id="event-1-2", depends="event-1")
   TEST("after recv event-1, if recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(2)));
   }

   // @test(id="event-2-1", depends="event-2")
   TEST("after recv event-2, if recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(1)));
   }

   // @test(depends="event-1")
   TEST("after recv event-1, if recv event-3, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(depends="event-1-2")
   TEST("after recv event-1-2, if recv event-3, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(depends="event-2-1")
   TEST("after recv event-2-1, if recv event-3, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(SimpleEventInfo(3)));
   }
};

FIXTURE(mt4)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __sequential(__join(2), __wait(1)))
       , __fork(2, __wait(2))
       , __join(1, 2)
       , __wait(3))
   ) trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   // @test(id="event-2")
   TEST("after recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(2)));
   }

   TEST("after recv event-1, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(1)));
   }

   TEST("after recv event-3, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(id="event-2-1", depends="event-2")
   TEST("after recv event-2, if recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(SimpleEventInfo(1)));
   }

   // @test(depends="event-2")
   TEST("after recv event-2, if recv event-3, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(SimpleEventInfo(3)));
   }

   // @test(depends="event-2-1")
   TEST("after recv event-2-1, if recv event-3, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(SimpleEventInfo(3)));
   }
};

FIXTURE(mt5)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __throw(ERROR1))
       , __wait(2))
   , __finally(__throw(ERROR2))
   ) trans;

   TEST("should return last error")
   {
      ASSERT_EQ(ERROR2, trans.start());
   }
};

FIXTURE(mt6)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __throw(ERROR1))
       , __wait(2))
   ) trans;

   TEST("should return last error")
   {
      ASSERT_EQ(ERROR1, trans.start());
   }
};

FIXTURE(mt7)
{
   __prot_mt_transaction
   ( __sequential
       ( __fork(1, __throw(ERROR1))
       , __wait(2))
   ) trans;

   TEST("should return last error")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.start());
   }
};

#define EVENT(n) SimpleEventInfo(n)
#define TIMER_EVENT(n) EVENT(n + 400)

const ActionThreadId WAIT_CANCEL_THREAD         = 1;
const ActionThreadId X1_RECFG_THEAD             = 2;
const ActionThreadId X1_REESTAB_SRB_THEAD       = 3;
const ActionThreadId X2_SN_STATUS_THREAD        = 4;
const ActionThreadId RNLU_ENDMARK_THREAD        = 5;

const EventId X2_HO_REQ              = 1;
const EventId BRS_SETUP_TUNNEL_ACK   = 2;
const EventId RNLU_CFG_ACK           = 3;
const EventId BB_CFG_ACK             = 4;
const EventId S1_PATH_SWITCH_ACK     = 5;
const EventId EV_SN_STATUS           = 6;
const EventId EV_X1_RRC_REESTAB_REQ  = 7;
const EventId EV_X1_RECFG_CMP        = 8;
const EventId EV_CANCEL              = 9;
const EventId BRS_RELEASE_TUNNEL_ACK = 10;
const EventId EV_X1_REESTAB_RSP      = 11;

const TimerId BRS_TIMER             = 1;
const TimerId X1_RECFG_TIMER        = 2;
const TimerId ENDMARK_TIMER         = 3;
const TimerId S1_PATH_SWITCH_TIMER  = 4;

FIXTURE(Attach)
{
   __def(X1RrcConnRequest)    __as ( __nop() );
   __def(RrmAdmit)            __as ( __nop() );
   __def(RnluSrb1Cfg)         __as ( __wait(RNLU_CFG_ACK) );
   __def(BbSrb1Cfg)           __as ( __wait(BB_CFG_ACK) );
   __def(X1RrcConnSetup)      __as ( __wait(3) );
   __def(RrmConfirm)          __as ( __nop() );
   __def(RnluConfirm)         __as ( __nop() );
   __def(BbConfirm)           __as ( __nop() );
   __def(X1RrcConnReject)     __as ( __nop() );
   __def(X1UeCapQuery)        __as ( __wait(4) );
   __def(S1InitUeReq)         __as ( __nop() );
   __def(CpmS1RouteSelectRsp) __as ( __wait(5) );
   __def(S1InitUeContextReq)  __as ( __wait(6) );
   __def(X1SecurityActivate)  __as ( __wait(7) );
   __def(RnluSecurityActivate) __as ( __nop() );
   __def(RrmInitUeContextDrbAdmit) __as ( __nop() );
   __def(RnluDrbCfg)         __as ( __wait(RNLU_CFG_ACK) );
   __def(BbDrbCfg)           __as ( __wait(BB_CFG_ACK) );
   __def(DbReadDrbParams)    __as ( __nop() );
   __def(BrsNormalTunnelSetup)   __as ( __wait(BRS_SETUP_TUNNEL_ACK));
   __def(BrsNormalFwdTunnelSetup)   __as ( __wait(BRS_SETUP_TUNNEL_ACK));
   __def(BrsReleaseNormalTunnel)       __as( __wait(BRS_SETUP_TUNNEL_ACK) );
   __def(X1SendRecfg)                __as( __wait(11) );
   __def(S1InitUeContextReqSave) __as( __wait(12) );

   __def(Rollback) __as ( __nop() );

   __def(SMC) __as
   ( __sequential
       ( __fork(2, __apply(X1SecurityActivate))
       , __apply(RnluSecurityActivate))
   );

   __def(S1InitUe) __as
   ( __sequential
       ( __apply(S1InitUeReq)
       , __concurrent(__apply(CpmS1RouteSelectRsp), __apply(S1InitUeContextReq)))
   );
   ////////////////////////////////////////////////
   __def(LocalCfg, __params(__action(RNLU_CFG), __action(BB_CFG))) __as
   ( __timer_prot(1, __concurrent(RNLU_CFG, BB_CFG))
   );

   ////////////////////////////////////////////////
   __def(LocalConfirm) __as
   ( __sequential
       ( __apply(RrmConfirm)
       , __apply(RnluConfirm)
       , __apply(BbConfirm))
   );

   ////////////////////////////////////////////////
   __def(RrcConnPrepare) __as_procedure
   ( __sequential
      ( __apply(X1RrcConnRequest)
      , __apply(RrmAdmit)
      , __apply(LocalCfg, __with(__apply(RnluSrb1Cfg), __apply(BbSrb1Cfg))))
   , __finally
      ( __on_fail(__sequential
                    ( __apply(X1RrcConnReject)
                    , __apply(Rollback))))
   );

   ////////////////////////////////////////////////
   __def(RrcConnExecute) __as
   ( __sequential
      ( __apply(X1RrcConnSetup)
      , __fork(1, __apply(X1UeCapQuery))
      , __apply(RrmConfirm))
   );

   ////////////////////////////////////////////////
   __def(RrcConn) __as_procedure
   ( __sequential
       ( __apply(RrcConnPrepare)
       , __apply(RrcConnExecute))
   );

   __def(DrbSetupPrepare) __as_procedure
   ( __sequential
       ( __apply(RrmInitUeContextDrbAdmit)
       , __apply(DbReadDrbParams)
       , __apply(BrsNormalTunnelSetup)
       , __apply(LocalCfg, __with(__apply(RnluDrbCfg), __apply(BbDrbCfg))))
   , __finally( __on_fail(__apply(Rollback)) )
   );

   __def(DrbSetupExecute) __as
   ( __sequential
       ( __apply(X1SendRecfg)
       , __apply(LocalConfirm))
   );

   __def(DrbSetup) __as_procedure
   ( __sequential
       ( __apply(DrbSetupPrepare)
       , __apply(DrbSetupExecute))
   );

   __def(S1InitUeContextRsp) __as( __nop() );

   __def(InitUeContextSetup) __as_procedure
   ( __sequential
       ( __apply(S1InitUeContextReqSave)
       , __apply(SMC)
       , __apply(DrbSetup))
   , __finally
       ( __apply(S1InitUeContextRsp) )
   );

   __mt_transaction
   ( __sequential
       ( __apply(RrcConn)
       , __timer_prot(2, __apply(S1InitUe))
       , __apply(InitUeContextSetup))
   ) trans;

   ///////////////////////////////////////////////////////////
   __def(S1ErabSetupReq) __as(__nop());

   __def(ErabSetupPrepare) __as_procedure
   ( __sequential
       ( __apply(S1ErabSetupReq)
       , __apply(RrmAdmit)
       , __apply(DbReadDrbParams)
       , __timer_prot(1, __apply(BrsNormalTunnelSetup))
       , __apply(LocalCfg, __with(__apply(RnluDrbCfg), __apply(BbDrbCfg))))
   , __finally(__apply(Rollback))
   );

   __def(X1RecfgCmp) __as ( __wait(EV_X1_RECFG_CMP) );



   __def(ErabSetupExecute) __as
   ( __sequential
       ( __apply(X1SendRecfg)
       , __fork(X1_RECFG_THEAD, __timer_prot(2, __apply(X1RecfgCmp)))
       , __apply(LocalConfirm))
   );

   __def(S1ErabSetupRsp) __as ( __nop() );

   __mt_transaction
   ( __sequential
       ( __apply(ErabSetupPrepare)
       , __apply(ErabSetupExecute))
   , __finally
       ( __sequential
           ( __apply(S1ErabSetupRsp)
           , __join(X1_RECFG_THEAD)))
   ) erabSetup;


   __def(X2HodReq)        __as ( __wait(X2_HO_REQ) );
   __def(X2HodAck)        __as ( __nop() );
   __def(WaitX2HosCancel) __as ( __wait(EV_CANCEL));

   __def(SnUpdate)     __as ( __wait(EV_SN_STATUS) );
   __def(S1PathSwitch) __as ( __wait(S1_PATH_SWITCH_ACK) );
   __def(RnluUlSwitch) __as ( __nop() );
   __def(BrsReleaseFwdTunnel) __as ( __nop() );
   __def(X2ReleaseSrc) __as ( __nop() );
   __def(RnluWaitEndmark) __as ( __wait(20) );
   __def(BrsAddrUpdate)   __as ( __wait(20) );
   __def(RnluAddrUpdate)  __as ( __nop() );
   __def(TransDataConfirm)  __as ( __nop() );


   /////////////////////////////////////////////////////////////
   __def(X2HodPrepare) __as_procedure
   ( __sequential
       ( __apply(X2HodReq)
       , __apply(RrmAdmit)
       , __apply(DbReadDrbParams)
       , __timer_prot(BRS_TIMER, __apply(BrsNormalFwdTunnelSetup))
       , __apply(LocalCfg, __with(__apply(RnluDrbCfg), __apply(BbDrbCfg))))
   , __finally(__on_fail_except(E_CANCELED, __apply(X2HodAck)))
   );

   /////////////////////////////////////////////////////////////
   __def(PathSwitch) __as
   ( __sequential
      ( __timer_prot(S1_PATH_SWITCH_TIMER, __apply(S1PathSwitch))
      , __apply(BrsAddrUpdate)
      , __apply(RnluAddrUpdate))
   );

   /////////////////////////////////////////////////////////////
   __def(CfgSwitch) __as
   (__sequential
      ( __fork(RNLU_ENDMARK_THREAD, __apply(RnluWaitEndmark))
      , __apply(PathSwitch)
      , __apply(RnluUlSwitch)
      , __void(__timer_prot(ENDMARK_TIMER, __join(RNLU_ENDMARK_THREAD))))
   );

   /////////////////////////////////////////////////////////////
   __def(ResourceConfirm) __as
   ( __sequential
       ( __apply(RrmConfirm)
       , __apply(TransDataConfirm))
   );

   /////////////////////////////////////////////////////////////
   __def(X1RrcReestabReq)    __as ( __wait(EV_X1_RRC_REESTAB_REQ) );
   __def(X1ReestabReq)       __as ( __wait(EV_X1_REESTAB_RSP) );
   __def(X1RrcReestabReject) __as ( __nop() );

   /////////////////////////////////////////////////////////////
   __def(ReestabSrbPrepare) __as_procedure
   ( __sequential
       ( __apply(X1RrcReestabReq)
       , __apply(RrmAdmit)
       , __apply(LocalCfg, __with(__apply(RnluDrbCfg), __apply(BbDrbCfg))))
    , __finally(__on_fail(__apply(X1RrcReestabReject)))
    );

   /////////////////////////////////////////////////////////////
   __def(ReestabSrbExecute) __as
   ( __sequential
       ( __timer_prot(X1_RECFG_TIMER, __apply(X1ReestabReq))
       , __apply(RrmConfirm))
   );

   /////////////////////////////////////////////////////////////
   __def(ReestabSrb) __as
   ( __sequential
       ( __apply(ReestabSrbPrepare)
       , __apply(ReestabSrbExecute))
   );

   /////////////////////////////////////////////////////////////
   __def(X1ReestabSrb) __as
   ( __sequential
       ( __peek(EV_X1_RRC_REESTAB_REQ)
       , __fork(X1_REESTAB_SRB_THEAD, __apply(ReestabSrb)))
   );

   /////////////////////////////////////////////////////////////
   __def(X1WaitRecfgCmp) __as
   (__exclusive
      ( __wait(EV_X1_RECFG_CMP)
      , __apply(X1ReestabSrb)));

   /////////////////////////////////////////////////////////////
   __def(X2HodExecute) __as_procedure
   ( __sequential
      ( __apply(ResourceConfirm)  // must confirm RRM & TransData First.
      , __fork(X2_SN_STATUS_THREAD,  __apply(SnUpdate))
      , __timer_prot(X1_RECFG_TIMER, __apply(X1WaitRecfgCmp))
      , __apply(CfgSwitch)
      , __apply(BrsReleaseFwdTunnel))
   , __finally(__on_fail_except(E_CANCELED, __apply(X2ReleaseSrc)))
   );

   /////////////////////////////////////////////////////////////
   __def(X1Recfg) __as
   ( __sequential
       ( __apply(X1SendRecfg)
       , __timer_prot(X1_RECFG_TIMER, __apply(X1WaitRecfgCmp)))
   );

   struct IsX1Connected
   {
      bool operator()(const TransactionInfo&)
      { return true; }
   };

   struct HasFailedErab
   {
      bool operator()(const TransactionInfo&)
      { return true; }
   };

   /////////////////////////////////////////////////////////////
   __def(CleanupFailedErab) __as
   ( __sequential
       ( __apply(RrmAdmit)
       , __apply(BrsReleaseNormalTunnel)
       , __apply(LocalCfg, __with(__apply(RnluDrbCfg), __apply(BbDrbCfg)))
       , __optional(IsX1Connected, __apply(X1Recfg))
       , __apply(RnluConfirm)
       , __apply(BbConfirm)
       , __apply(TransDataConfirm))
   );

   /////////////////////////////////////////////////////////////
   __def(X2HodCleanup) __as
   ( __optional(HasFailedErab, __apply(CleanupFailedErab)));

   /////////////////////////////////////////////////////////////
   __mt_transaction
   ( __sequential
       ( __fork(WAIT_CANCEL_THREAD, __sequential
                                      ( __apply(WaitX2HosCancel)
                                      , __throw(E_CANCELED)))
       , __apply(X2HodPrepare)
       , __apply(X2HodExecute)
       , __apply(X2HodCleanup))
   )x2hod;

   struct MyTimerInfo : TimerInfo
   {
      U32 getTimerLen(const TimerId) const
      {
         return 10;
      }
   } timerInfo;

   SETUP()
   {
      x2hod.updateTimerInfo(timerInfo);

      ASSERT_EQ(TSL_CONTINUE, x2hod.start());
   }

   // @test(id="x2-hod-req")
   TEST("after recv X2_HOD_REQ, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(X2_HO_REQ)));
   }

   // @test(depends="x2-hod-req")
   TEST("after recv X2_HO_REQ, if BRS timeout, should return TSL_TIMEDOUT")
   {
      ASSERT_EQ(TSL_TIMEDOUT, x2hod.handleEvent(TIMER_EVENT(BRS_TIMER)));
   }

   // @test(id="brs-setup", depends="x2-hod-req")
   TEST("after recv X2_HO_REQ, if recv BRS_SETUP_TUNNEL_ACK, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(BRS_SETUP_TUNNEL_ACK)));
   }

   // @test(id="rnlu-bb-setup", depends="brs-setup")
   TEST("after tunnel setup, if recv BB_CFG_ACK, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(BB_CFG_ACK)));
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(RNLU_CFG_ACK)));
   }

   // @test(depends="rnlu-bb-setup")
   TEST("after rnlu & bb setup, if recv X1_RECFG_TIMER, should return TSL_TIMEDOUT")
   {
      ASSERT_EQ(TSL_TIMEDOUT, x2hod.handleEvent(TIMER_EVENT(X1_RECFG_TIMER)));
   }

   // @test(depends="rnlu-bb-setup")
   TEST("after rnlu && bb setup, if recv EV_CANCEL, should return E_CANCELED")
   {
      ASSERT_EQ(E_CANCELED, x2hod.handleEvent(EVENT(EV_CANCEL)));
   }

   // @test(id="recfg", depends="rnlu-bb-setup")
   TEST("after rnlu & bb setup, if recv X1_RECFG_CMP, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(EV_X1_RECFG_CMP)));
   }

   // @test(id="reestab", depends="rnlu-bb-setup")
   TEST("after rnlu & bb setup, if recv X1_RECFG_CMP, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(EV_X1_RRC_REESTAB_REQ)));
   }

   // @test(depends="reestab")
   TEST("after reestab, if recv S1_PATH_SWITCH_ACK, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, x2hod.handleEvent(EVENT(S1_PATH_SWITCH_ACK)));
   }

   // @test(depends="recfg")
   TEST("after recfg, if recv EV_CANCEL, should return E_CANCELED")
   {
      ASSERT_EQ(E_CANCELED, x2hod.handleEvent(EVENT(EV_CANCEL)));
   }
};

FIXTURE(Status)
{
   __mt_transaction
   ( __sequential
       ( __fork(1, __sequential
                     ( __wait(1)
                     , __throw(ERROR1)))
       , __join(1)
       , __wait(2))
   , __finally
       ( __on_status(ERROR1, __wait(3)))
   )trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   // @test(id="event-1")
   TEST("after start, if recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(EVENT(1)));
   }

   // @test(depends="event-1")
   TEST("after recv event-1, if recv event-3, should return ERROR1")
   {
      ASSERT_EQ(ERROR1, trans.handleEvent(EVENT(3)));
   }

   // @test(depends="event-1")
   TEST("after recv event-1, if recv event-2, should return TSL_UNKNOWN_EVENT")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans.handleEvent(EVENT(2)));
   }
};

FIXTURE(Status1)
{
   __mt_transaction
   ( __sequential
       ( __fork(1,  __wait(1))
       , __fork(2, __sequential
                     ( __wait(2)
                     , __throw(ERROR1)))
       , __join(1))
   , __finally
       ( __on_status(ERROR1, __wait(3)))
   )trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   // @test(id="event-2")
   TEST("after start, if recv event-2, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(EVENT(2)));
   }

   // @test(depends="event-2")
   TEST("after recv event-2, if recv event-3, should return ERROR1")
   {
      ASSERT_EQ(ERROR1, trans.handleEvent(EVENT(3)));
   }
};

FIXTURE(peek)
{
   __mt_transaction
   ( __sequential(__peek(1), __wait(1))
   )trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   TEST("after start, if recv event-1, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(EVENT(1)));
   }
};

FIXTURE(safe_mode)
{
   __mt_transaction
   ( __sequential
       ( __wait(1)
       , __safe_mode
           (__sequential
              ( __fork(1, __wait(2))
              , __wait(3)
              , __join(1)))
       , __wait(4))
   )trans;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, trans.start());
   }

   TEST("after start, if stop, should return stop cause")
   {
      ASSERT_EQ(ERROR1, trans.stop(ERROR1));
   }

   // @test(id="ev-1")
   TEST("after started, if recv event-1, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(EVENT(1)));
   }

   // @test(id="stop", depends="ev-1")
   TEST("after recv event-1, if stop, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.stop(ERROR1));
   }

   // @test(id="safe", depends="stop")
   TEST("after stop, is recv event-2, event-3, should return TSL_CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(EVENT(2)));
      ASSERT_EQ(TSL_CONTINUE, trans.handleEvent(EVENT(3)));
   }

   // @test(depends="safe")
   TEST("after safe mode, if stop, should return stop cause")
   {
      ASSERT_EQ(ERROR1, trans.stop(ERROR1));
   }

   // @test(depends="safe")
   TEST("after safe mode, if recv event-4, should return TSL_SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, trans.handleEvent(EVENT(4)));
   }
};

