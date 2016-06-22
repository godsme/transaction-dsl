
/*
 * SchedSwitchCaseAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include <trans-dsl/sched/action/SchedSwitchCaseAction.h>
#include <trans-dsl/sched/concept/TransactionContext.h>

TSL_NS_BEGIN

using namespace cub;

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
   if(selectedAction == 0) return TSL_SUCCESS;

   return selectedAction->exec(context);
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   if(selectedAction == 0) return TSL_FATAL_BUG;
   return selectedAction->handleEvent(context, event);
}

//////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::stop(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return TSL_SUCCESS;
   return selectedAction->stop(context, cause);
}

//////////////////////////////////////////////////////////////////////
void SchedSwitchCaseAction::kill(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return;
   selectedAction->kill(context, cause);
}

TSL_NS_END

