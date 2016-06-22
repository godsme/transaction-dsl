/*
 * SchedConcurrentAction.cc
 *
 * Created on: Apr 22, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#include "trans-dsl/sched/action/SchedConcurrentAction.h"
#include "trans-dsl/utils/RuntimeContextAutoSwitch.h"

///////////////////////////////////////////////////////////////////////
SchedConcurrentAction::SchedConcurrentAction()
  : stopping(false)
{
}

////////////////////////////////////////////////////////////////////
bool SchedConcurrentAction::hasWorkingThreads() const
{
   return not threads.isEmpty();
}

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::getFinalStatus() const
{
   return hasWorkingThreads() ? CONTINUE : objectStatus;
}

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::process(const ActionStatus status,
         TransactionContext& context)
{
   if (status.eventNotAccepted())
   {
      return status;
   }

   if(ActionStatus(getStatus()).isFailed())
   {
      doStop(context, getStatus());
   }

   return getFinalStatus();
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::doneCheck(const ActionStatus status, Thread& thread)
{
   if (not status.isWorking())
   {
      threads.erase(thread);
   }

   if(status.isFailed())
   {
      reportFailure(status);
   }

   return status;
}

////////////////////////////////////////////////////////////////////
#define DONE_CHECK(thread, method) doneCheck(thread->method, thread)

////////////////////////////////////////////////////////////////////
#define FOREACH_THREAD(thread) \
      LIST_FOREACH(LinkedActionThread, thread, threads)

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::doExec(TransactionContext& context)
{
   FOREACH_THREAD(thread)
   {
      ActionStatus status = DONE_CHECK(thread, exec(context));
      if (status.isFailed())
      {
         return status;
      }
   }

   return SUCCESS;
}

////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::doStop(TransactionContext& context, const Status cause)
{
   if(stopping) return;

   FOREACH_THREAD(thread)
   {
      DONE_CHECK(thread, stop(context, cause));
   }

   stopping = true;
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::doHandleEvent(TransactionContext& context, const Event& event)
{
   FOREACH_THREAD(thread)
   {
      ActionStatus status = DONE_CHECK(thread, handleEvent(context, event));
      if (status.eventAccepted())
      {
         return status;
      }
   }

   return UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////
struct SchedConcurrentAction::AutoSwitch : RuntimeContextAutoSwitch
{
   AutoSwitch(SchedConcurrentAction& action, TransactionContext& context)
        : RuntimeContextAutoSwitch(action, action.parent, context)
   {
   }
};

///////////////////////////////////////////////////////////////////////
#define __AUTO_SWITCH()  AutoSwitch autoSwitch(*this, context)

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::exec(TransactionContext& context)
{
   __AUTO_SWITCH();
   return process(doExec(context), context);
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::handleEvent(TransactionContext& context, const Event& event)
{
   __AUTO_SWITCH();
   return process(doHandleEvent(context, event), context);
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::stop(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();

   doStop(context, cause);

   return getFinalStatus();
}

///////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::kill(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();

   FOREACH_THREAD(thread)
   {
      thread->kill(context, cause);
   }
}

///////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::addThread(LinkedActionThread& thread)
{
   threads.pushBack(thread);
}
