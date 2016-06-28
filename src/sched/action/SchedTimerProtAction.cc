/*
 * SchedTimerProtAction.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include <cub/base/Assertions.h>
#include <trans-dsl/sched/action/SchedTimerProtAction.h>
#include <trans-dsl/sched/concept/TimerInfo.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <trans-dsl/utils/RelativeTimer.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/sched/concept/TransactionInfo.h>
#include <event/concept/Event.h>

TSL_NS_BEGIN

using namespace cub;

namespace details
{
   TimerProtActionState::TimerProtActionState() : state(IDLE) {}

   void TimerProtActionState::start()
   {
      state = WORKING;
   }

   void TimerProtActionState::stop(const Status status)
   {
      if(ActionStatus(status).isWorking())
      {
         state = STOPPING;
      }
      else
      {
         state = IDLE;
      }
   }

   bool TimerProtActionState::isDone() const
   {
      return state == IDLE;
   }

   bool TimerProtActionState::isStopping() const
   {
      return state == STOPPING;
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction ::startTimer(TransactionContext& context)
   {
      TimerInfo* timerInfo = com::unknown_cast<TimerInfo>(&context);
      CUB_ASSERT_VALID_PTR(timerInfo);

      return ROLE(RelativeTimer).start(*timerInfo);
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction ::exec(TransactionContext& context)
   {
      ActionStatus status = ROLE(SchedAction).exec(context);
      if(status.isWorking())
      {
         ROLE(TimerProtActionState).start();

         CUB_ASSERT_SUCC_CALL(startTimer(context));
      }

      return status;
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction ::handleEvent(TransactionContext& context, const ev::Event& event)
   {
      if(ROLE(RelativeTimer).matches(event))
      {
         ROLE(RelativeTimer).stop();
         event.consume();

         return ActionStatus(getTimeoutStatus()).isWorking() ? TSL_TIMEDOUT : getTimeoutStatus();
      }

      ActionStatus status = ROLE(SchedAction).handleEvent(context, event);
      if(status.isWorking())
      {
         return status;
      }

      ROLE(RelativeTimer).stop();
      ROLE(TimerProtActionState).stop(status);

      return status;
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction::stop(TransactionContext& context, const Status cause)
   {
      ROLE(RelativeTimer).stop();

      ActionStatus status = ROLE(SchedAction).stop(context, cause);

      ROLE(TimerProtActionState).stop(status);

      if(status.isWorking())
      {
         return TSL_SUCCESS;
      }

      return status;
   }

   //////////////////////////////////////////////////////////////////////////////////
   void TimerProtAction ::kill(TransactionContext& context, const Status cause)
   {
      ROLE(RelativeTimer).stop();
      ROLE(SchedAction).kill(context, cause);
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtFinalAction::exec(TransactionContext& context)
   {
      if(ROLE(TimerProtActionState).isDone())
      {
         return TSL_SUCCESS;
      }

      if(ROLE(TimerProtActionState).isStopping())
      {
         return TSL_CONTINUE;
      }

      return ROLE(SchedAction).stop(context, context.ROLE(TransactionInfo).getStatus());
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtFinalAction::handleEvent(TransactionContext& context, const ev::Event& event)
   {
      return ROLE(SchedAction).handleEvent(context, event);
   }

   //////////////////////////////////////////////////////////////////////////////////
   void TimerProtFinalAction::kill(TransactionContext& context, const Status cause)
   {
      ROLE(SchedAction).kill(context, cause);
   }
}

TSL_NS_END

