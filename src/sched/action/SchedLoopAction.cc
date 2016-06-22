/*
 * SchedLoopAction.cc
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/action/SchedLoopAction.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/sched/concept/TransactionInfo.h"

TSL_NS_BEGIN

using namespace cub;

///////////////////////////////////////////////////////////
SchedLoopAction::SchedLoopAction() : state(IDLE), stopCause(TSL_SUCCESS)
{
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::restart(TransactionContext& context)
{
   if(state == STOPPED) return TSL_RESTART_REQUIRED;

   while(1)
   {
      ActionStatus status = doRestart(context);
      if(status != TSL_RESTART_REQUIRED)
      {
         return status;
      }
   }

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doExec(TransactionContext& context)
{
   if(shouldExecute(context))
   {
      return restart(context);
   }

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::getFinalStatus(const ActionStatus status)
{
   if(status == TSL_RESTART_REQUIRED)
   {
      return state == STOPPED ? stopCause : TSL_FATAL_BUG;
   }

   if(!status.isWorking())
   {
      state = IDLE;
   }
   else
   {
      state = EXEC;
   }

   return status;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::exec(TransactionContext& context)
{
   return getFinalStatus(doExec(context));
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doRestart(TransactionContext& context)
{
   reset();

   return ROLE(SchedAction).exec(context);
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doHandleEvent(TransactionContext& context, const ev::Event& event)
{
   Status status = ROLE(SchedAction).handleEvent(context, event);
   if(status == TSL_RESTART_REQUIRED)
   {
      return restart(context);
   }

   return status;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return getFinalStatus(doHandleEvent(context, event));
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::stop(TransactionContext& context, const Status cause)
{
   if(state == EXEC)
   {
      state = STOPPED;
      stopCause = cause;

      return getFinalStatus(ROLE(SchedAction).stop(context, cause));
   }

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////
void SchedLoopAction::kill(TransactionContext& context, const Status cause)
{
   if(state == EXEC)
   {
      state = IDLE;
      ROLE(SchedAction).kill(context, cause);
   }
}

///////////////////////////////////////////////////////////
Status LoopCondCheckAction::exec(TransactionContext& context)
{
   if(shouldExecute(context))
   {
      return TSL_RESTART_REQUIRED;
   }

   return context.getTransactionInfo().getStatus();
}

///////////////////////////////////////////////////////////
Status LoopCondCheckAction::handleEvent(TransactionContext&, const ev::Event&)
{
   return TSL_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////
void LoopCondCheckAction::kill(TransactionContext&, const Status)
{
}

TSL_NS_END

