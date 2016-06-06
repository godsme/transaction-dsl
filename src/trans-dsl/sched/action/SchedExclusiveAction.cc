/*
 * SchedExclusiveAction.cc
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */


#include "trans-dsl/sched/action/SchedExclusiveAction.h"
#include "trans-dsl/utils/ActionStatus.h"

///////////////////////////////////////////////////////////////////////////
SchedExclusiveAction::SchedExclusiveAction()
  : selectedAction(0)
{
}

///////////////////////////////////////////////////////////////////////////
Status SchedExclusiveAction::exec(TransactionContext& context)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      ActionStatus status = action->exec(context);
      if(status.isFailed())
      {
         return status;
      }
      else if(status.isDone())
      {
         actions.erase(action);
      }
   }

   return actions.isEmpty() ? SUCCESS : CONTINUE;
}

///////////////////////////////////////////////////////////////////////////
void SchedExclusiveAction::interruptOthers(TransactionContext& context)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      if(&(*action) != selectedAction)
      {
         action->kill(context, SUCCESS);
      }
   }
}

///////////////////////////////////////////////////////////////////////////
Status SchedExclusiveAction::selectAction(TransactionContext& context, const Event& event)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      ActionStatus status = action->handleEvent(context, event);
      if(status.eventAccepted())
      {
         selectedAction = &(*action);
         interruptOthers(context);

         return status;
      }
   }

   return UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////////
Status SchedExclusiveAction::handleEvent(TransactionContext& context, const Event& event)
{
   if(selectedAction == 0)
   {
      return selectAction(context, event);
   }
   else
   {
      return selectedAction->handleEvent(context, event);
   }
}

///////////////////////////////////////////////////////////////////////////
Status SchedExclusiveAction::stop(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0)
   {
      kill(context, cause);
      return cause;
   }
   else
   {
      return selectedAction->stop(context, cause);
   }
}

///////////////////////////////////////////////////////////////////////////
void SchedExclusiveAction::kill(TransactionContext& context, const Status cause)
{
   if(selectedAction != 0)
   {
      selectedAction->kill(context, cause);
      return;
   }

   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      action->kill(context, cause);
   }
}

///////////////////////////////////////////////////////////////////////////
void SchedExclusiveAction::addAction(LinkedSchedAction& action)
{
   actions.pushBack(action);
}
