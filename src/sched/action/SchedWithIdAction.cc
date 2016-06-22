/*
 * SchedWithIdAction.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/sched/action/SchedWithIdAction.h>
#include <trans-dsl/utils/GofState.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/sched/concept/TransactionListener.h>
#include <event/concept/Event.h>

TSL_NS_BEGIN

using namespace cub;

__DECL_STATE_INTERFACE(SchedWithIdAction);

///////////////////////////////////////////////////////////////////////
__DEF_STATE_CLASS(SchedWithIdAction, Idle)
{
   OVERRIDE(Status exec(SchedWithIdAction& __THIS__, TransactionContext& context))
   {
      context.ROLE(TransactionListener).onActionStarting(__THIS__.getActionId());

      ActionStatus status = __THIS__.ROLE(SchedAction).exec(context);
      if(status.isWorking())
      {
         context.ROLE(TransactionListener).onActionStarted(__THIS__.getActionId());
         return __THIS__.__GOTO_STATE(Working);
      }

      context.ROLE(TransactionListener).onActionDone(__THIS__.getActionId(), status);

      return __THIS__.__GOTO_STATE(Done);
   }
};

///////////////////////////////////////////////////////////////////////
__DEF_STATE_CLASS(SchedWithIdAction, Working)
{
   OVERRIDE(Status handleEvent(SchedWithIdAction& __THIS__, TransactionContext& context, const ev::Event& event))
   {
      ActionStatus status = __THIS__.ROLE(SchedAction).handleEvent(context, event);
      if(event.isConsumed())
      {
         context.ROLE(TransactionListener).onActionEventConsumed(__THIS__.getActionId(), event);
      }

      if(status.isWorking())
      {
         return status;
      }

      context.ROLE(TransactionListener).onActionDone(__THIS__.getActionId(), status);

      return __THIS__.__GOTO_STATE(Done);
   }

   OVERRIDE(Status stop(SchedWithIdAction& __THIS__, TransactionContext& context, const Status cause))
   {
      context.ROLE(TransactionListener).onActionStartStopping(__THIS__.getActionId(), cause);

      ActionStatus status = __THIS__.ROLE(SchedAction).stop(context, cause);
      if(status.isWorking())
      {
         context.ROLE(TransactionListener).onActionStoppingStarted(__THIS__.getActionId());

         return __THIS__.__GOTO_STATE(Stopping);
      }

      context.ROLE(TransactionListener).onActionStopped(__THIS__.getActionId(), status);

      return __THIS__.__GOTO_STATE(Done);
   }

   OVERRIDE(void kill(SchedWithIdAction& __THIS__, TransactionContext& context, const Status cause))
   {
      context.ROLE(TransactionListener).onActionKilled(__THIS__.getActionId(), cause);
      __THIS__.ROLE(SchedAction).kill(context, cause);

      __THIS__.____GOTO_STATE(Done, TSL_SUCCESS);
   }
};

__DEF_STATE_CLASS(SchedWithIdAction, Stopping)
{
   OVERRIDE(Status handleEvent(SchedWithIdAction& __THIS__, TransactionContext& context, const ev::Event& event))
   {
      ActionStatus status = __THIS__.ROLE(SchedAction).handleEvent(context, event);
      if(event.isConsumed())
      {
         context.ROLE(TransactionListener).onStoppingEventConsumed(__THIS__.getActionId(), event);
      }

      if(status.isWorking())
      {
         return status;
      }

      context.ROLE(TransactionListener).onActionStopped(__THIS__.getActionId(), status);

      return __THIS__.__GOTO_STATE(Done);
   }

   OVERRIDE(void kill(SchedWithIdAction& __THIS__, TransactionContext& context, const Status cause))
   {
      context.ROLE(TransactionListener).onActionKilled(__THIS__.getActionId(), cause);
      __THIS__.ROLE(SchedAction).kill(context, cause);

      __THIS__.____GOTO_STATE(Done, TSL_SUCCESS);
   }
};

__DEF_STATE_CLASS(SchedWithIdAction, Done)
{

};


///////////////////////////////////////////////////////////////////////
__DEF_STATE(SchedWithIdAction, Idle)
__DEF_STATE(SchedWithIdAction, Working)
__DEF_STATE(SchedWithIdAction, Stopping)
__DEF_STATE(SchedWithIdAction, Done)

///////////////////////////////////////////////////////////////////////
SchedWithIdAction::SchedWithIdAction()
  : state(&SchedWithIdAction::Idle::getInstance())
{
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::exec(TransactionContext& context)
{
   return state->exec(*this, context);
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return state->handleEvent(*this, context, event);
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::stop(TransactionContext& context, const Status cause)
{
   return state->stop(*this, context, cause);
}

///////////////////////////////////////////////////////////////////////
void SchedWithIdAction::kill(TransactionContext& context, const Status cause)
{
   state->kill(*this, context, cause);
}

TSL_NS_END

