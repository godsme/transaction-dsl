/*
 * ActionThread.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include <trans-dsl/sched/action/ActionThread.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <trans-dsl/utils/GofState.h>
#include <trans-dsl/utils/RuntimeContextAutoSwitch.h>

#include <cub/base/Status.h>
#include <event/concept/Event.h>

TSL_NS_BEGIN

using namespace cub;

__DEF_STATE_INTERFACE(ActionThread)
{
   virtual bool isWorking() const
   {
      return false;
   }
};

__DEF_STATE_CLASS(ActionThread, Idle)
{
   virtual Status exec(ActionThread& __THIS__, TransactionContext& context)
   {
      ActionStatus status = __THIS__.ROLE(SchedAction).exec(context);
      if(status.isWorking())
      {
         return __THIS__.__GOTO_STATE(Working);
      }

      return __THIS__.__GOTO_STATE(Done);
   }
};

__DEF_BASE_STATE_CLASS(ActionThread, WorkingState)
{
   virtual Status handleEvent(ActionThread& __THIS__, TransactionContext& context, const ev::Event& event)
   {
      ActionStatus status = __THIS__.ROLE(SchedAction).handleEvent(context, event);
      if(status.isWorking())
      {
         return status;
      }

      return __THIS__.__GOTO_STATE(Done);
   }

   void   kill(ActionThread& __THIS__, TransactionContext& context, const Status cause)
   {
      __THIS__.ROLE(SchedAction).kill(context, cause);
      __THIS__.____GOTO_STATE(Done, TSL_SUCCESS);
   }

   bool isWorking() const
   {
      return true;
   }
};

__DEF_DERIVED_STATE_CLASS(ActionThread, Working, WorkingState)
{
   Status stop(ActionThread& __THIS__, TransactionContext& context, const Status cause)
   {
      ActionStatus status = __THIS__.ROLE(SchedAction).stop(context, cause);
      if(status.isWorking())
      {
         return __THIS__.__GOTO_STATE(Stopping);
      }

      return __THIS__.__GOTO_STATE(Done);
   }
};

__DEF_DERIVED_STATE_CLASS(ActionThread, Stopping, WorkingState)
{
   Status stop(ActionThread&, TransactionContext&, const Status)
   {
      return TSL_CONTINUE;
   }
};

__DEF_STATE_CLASS(ActionThread, Done)
{
   virtual Status enter(ActionThread& __THIS__, TransactionContext&, const ActionStatus status)
   {
      __THIS__.reportFailure(status);

      return status;
   }
};

__DEF_STATE(ActionThread, Idle)
__DEF_STATE(ActionThread, Working)
__DEF_STATE(ActionThread, Stopping)
__DEF_STATE(ActionThread, Done)

ActionThread::ActionThread()
  : state(&Idle::getInstance())
{
}

struct ActionThread::AutoSwitch : RuntimeContextAutoSwitch
{
   AutoSwitch(ActionThread& thread, TransactionContext& context)
        : RuntimeContextAutoSwitch(thread, thread.parent, context)
   {
   }
};

#define __AUTO_SWITCH() AutoSwitch autoSwitch(*this, context)

Status ActionThread::exec(TransactionContext& context)
{
   __AUTO_SWITCH();
   return state->exec(*this, context);
}

Status ActionThread::handleEvent(TransactionContext& context, const ev::Event& event)
{
   __AUTO_SWITCH();

   Status status = TSL_CONTINUE;
   while(!event.isConsumed() && status == TSL_CONTINUE)
   {
     status = state->handleEvent(*this, context, event);
   }

   return status;
}

Status ActionThread::stop(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();
   return state->stop(*this, context, cause);
}

void ActionThread::kill(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();
   state->kill(*this, context, cause);
}

bool ActionThread::isWorking() const
{
   return state->isWorking();
}

TSL_NS_END

