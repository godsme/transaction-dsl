/*
 * SchedSequentialAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/action/SchedSequentialAction.h"

TSL_NS_BEGIN

using namespace cub;

///////////////////////////////////////////////////////////////
SchedSequentialAction::SchedSequentialAction() : current(0), finalStatus(TSL_SUCCESS)
{
}

///////////////////////////////////////////////////////////////
void SchedSequentialAction::pushBackAction(LinkedSchedAction& action)
{
   actions.pushBack(action);
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::forward(TransactionContext& context)
{
   while((current = actions.popFront()) != 0)
   {
      ActionStatus status = current->exec(context);
      if(!status.isDone())
      {
         return status;
      }
   }

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::getFinalStatus(const ActionStatus status,
         TransactionContext& context)
{
   if (status.isFailed())
   {
      current = 0;
      (void) stop(context, status);
   }

   if(status.isDone())
   {
      return finalStatus;
   }

   return status;
}

///////////////////////////////////////////////////////////////
#define FINAL_STATUS(status) getFinalStatus(status, context)

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::exec(TransactionContext& context)
{
   return FINAL_STATUS(forward(context));
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::doHandleEvent(TransactionContext& context, const ev::Event& event)
{
   if (current == 0)
   {
      return TSL_UNKNOWN_EVENT;
   }

   ActionStatus status = current->handleEvent(context, event);
   if(!status.isDone())
   {
      return status;
   }

   return forward(context);
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return FINAL_STATUS(doHandleEvent(context, event));
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::doStop(TransactionContext& context, const Status cause)
{
   if(!actions.isEmpty())
   {
      finalStatus = cause;
   }

   actions.clear();

   if (current != 0)
   {
      ActionStatus status = current->stop(context, cause);
      if(!status.isWorking())
      {
         current = 0;
      }

      return status;
   }

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::stop(TransactionContext& context, const Status cause)
{
   return FINAL_STATUS(doStop(context, cause));
}

///////////////////////////////////////////////////////////////
void SchedSequentialAction::kill(TransactionContext& context, const Status cause)
{
   actions.clear();

   if (current != 0)
   {
      current->kill(context, cause);
      current = 0;
   }
}

TSL_NS_END
