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

///////////////////////////////////////////////////////////
SchedLoopAction::SchedLoopAction() : state(IDLE), stopCause(SUCCESS)
{
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::restart(TransactionContext& context)
{
   if(state == STOPPED) return RESTART_REQUIRED;

   while(1)
   {
      ActionStatus status = doRestart(context);
      if(status != RESTART_REQUIRED)
      {
         return status;
      }
   }

   return SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doExec(TransactionContext& context)
{
   if(shouldExecute(context))
   {
      return restart(context);
   }

   return SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::getFinalStatus(const ActionStatus status)
{
   if(status == RESTART_REQUIRED)
   {
      return state == STOPPED ? stopCause : FATAL_BUG;
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
Status SchedLoopAction::doHandleEvent(TransactionContext& context, const Event& event)
{
   Status status = ROLE(SchedAction).handleEvent(context, event);
   if(status == RESTART_REQUIRED)
   {
      return restart(context);
   }

   return status;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::handleEvent(TransactionContext& context, const Event& event)
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

   return SUCCESS;
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
      return RESTART_REQUIRED;
   }

   return context.getTransactionInfo().getStatus();
}

///////////////////////////////////////////////////////////
Status LoopCondCheckAction::handleEvent(TransactionContext&, const Event&)
{
   return UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////
void LoopCondCheckAction::kill(TransactionContext&, const Status)
{
}

