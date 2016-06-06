/*
 * SchedTimerProtAction.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include "trans-dsl/sched/action/SchedTimerProtAction.h"
#include "trans-dsl/sched/concept/TimerInfo.h"
#include "trans-dsl/utils/ActionStatus.h"
#include "trans-dsl/utils/RelativeTimer.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "base/dci/Unknown.h"
#include "base/utils/Assertions.h"
#include "trans-dsl/sched/concept/TransactionInfo.h"
#include "event/concept/Event.h"

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
      TimerInfo* timerInfo = unknown_cast<TimerInfo>(&context);
      DCM_ASSERT_VALID_PTR(timerInfo);

      return ROLE(RelativeTimer).start(*timerInfo);
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction ::exec(TransactionContext& context)
   {
      ActionStatus status = ROLE(SchedAction).exec(context);
      if(status.isWorking())
      {
         ROLE(TimerProtActionState).start();

         DCM_ASSERT_SUCC_CALL(startTimer(context));
      }

      return status;
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtAction ::handleEvent(TransactionContext& context, const Event& event)
   {
      if(ROLE(RelativeTimer).matches(event))
      {
         ROLE(RelativeTimer).stop();
         event.consume();

         return ActionStatus(getTimeoutStatus()).isWorking() ? TIMEDOUT : getTimeoutStatus();
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
         return SUCCESS;
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
         return SUCCESS;
      }

      if(ROLE(TimerProtActionState).isStopping())
      {
         return CONTINUE;
      }

      return ROLE(SchedAction).stop(context, context.ROLE(TransactionInfo).getStatus());
   }

   //////////////////////////////////////////////////////////////////////////////////
   Status TimerProtFinalAction::handleEvent(TransactionContext& context, const Event& event)
   {
      return ROLE(SchedAction).handleEvent(context, event);
   }

   //////////////////////////////////////////////////////////////////////////////////
   void TimerProtFinalAction::kill(TransactionContext& context, const Status cause)
   {
      ROLE(SchedAction).kill(context, cause);
   }
}
