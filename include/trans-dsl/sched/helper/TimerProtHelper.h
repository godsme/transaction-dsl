/*
 * TimerProtHelper.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#ifndef TIMERPROTHELPER_H_
#define TIMERPROTHELPER_H_

#include "trans-dsl/sched/action/SchedTimerProtAction.h"
#include "trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h"
#include "trans-dsl/sched/action/Procedure.h"

TSL_NS_BEGIN

namespace details
{

   template<tsl::TimerId TIMER_ID, typename T_ACTION, cub::Status TIMEOUT_STATUS>
   struct SchedTimerProtAction
            : private TimerProtActionState
            , TimerProtAction
            , TimerProtFinalAction
   {
      SchedTimerProtAction() : timer(TIMER_ID) {}

   private:
      IMPL_ROLE(TimerProtActionState);

   private:
      mutable PlatformSpecifiedRelativeTimer timer;
      ROLE_PROTO_TYPE(RelativeTimer)
      {
         return timer;
      }

      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);

      OVERRIDE(cub::Status getTimeoutStatus() const)
      {
         return TIMEOUT_STATUS;
      }
   };

   template<TimerId TIMER_ID, typename T_ACTION, cub::Status TIMEOUT_STATUS = TSL_TIMEDOUT>
   struct TIMER_PROT__: Procedure
   {
   private:
      mutable SchedTimerProtAction<TIMER_ID, T_ACTION, TIMEOUT_STATUS> action;
      ROLE_PROTO_TYPE(SchedAction)
      {
         return (TimerProtAction&)action;
      }

      ROLE_PROTO_TYPE(FinalAction)
      {
         return (TimerProtFinalAction&)action;
      }

      OVERRIDE(bool isProtected() const)
      {
         return false;
      }
   };
}

TSL_NS_END

///////////////////////////////////////////////////////////////////////
#define __timer_prot(...) \
      tsl::details::TIMER_PROT__< __VA_ARGS__ >

///////////////////////////////////////////////////////////////////////

#endif /* TIMERPROTHELPER_H_ */
