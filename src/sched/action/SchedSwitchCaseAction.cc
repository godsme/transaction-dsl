
/*
 * SchedSwitchCaseAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include "trans-dsl/sched/action/SchedSwitchCaseAction.h"
#include "trans-dsl/sched/concept/TransactionContext.h"

///////////////////////////////////////////////////////////////////////////////////
SchedSwitchCaseAction::SchedSwitchCaseAction() :
    selectedAction(0)
{
}

///////////////////////////////////////////////////////////////////////////////////
void SchedSwitchCaseAction::pushBackActionPath(ActionPath& path)
{
   paths.pushBack(path);
}

///////////////////////////////////////////////////////////////////////////////////
SchedAction* SchedSwitchCaseAction::findMatchedAction(TransactionContext& context)
{
   LIST_FOREACH(ActionPath, i, paths)
   {
      if(i->shouldExecute(context.getTransactionInfo()))
      {
         return &(i->getAction());
      }
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::exec(TransactionContext& context)
{
   selectedAction = findMatchedAction(context);
   if(selectedAction == 0) return SUCCESS;

   return selectedAction->exec(context);
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::handleEvent(TransactionContext& context, const Event& event)
{
   if(selectedAction == 0) return FATAL_BUG;
   return selectedAction->handleEvent(context, event);
}

//////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::stop(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return SUCCESS;
   return selectedAction->stop(context, cause);
}

//////////////////////////////////////////////////////////////////////
void SchedSwitchCaseAction::kill(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return;
   selectedAction->kill(context, cause);
}
