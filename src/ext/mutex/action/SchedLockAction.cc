/*
 * SchedLockAction.cc
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <cub/base/Assertions.h>
#include <trans-dsl/ext/mutex/action/SchedLockAction.h>
#include <trans-dsl/ext/mutex/def/TransMutexAvailMsg.h>
#include <trans-dsl/ext/mutex/concept/TransMutexScheduler.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <event/concept/Event.h>

TSL_NS_BEGIN

using namespace cub;

///////////////////////////////////////////////////////////////////////////////////////////
SchedLockAction::SchedLockAction() : waiting(true)
{
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::lock(TransactionContext& context)
{
   TransMutexScheduler* mutex = com::unknown_cast<TransMutexScheduler>(&context);
   CUB_ASSERT_VALID_PTR(mutex);

   ActionStatus status = mutex->lock(getMutexId());
   if(!status.isDone())
   {
      return status;
   }

   waiting = false;

   return TSL_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::unlock(TransactionContext& context)
{
   TransMutexScheduler* mutex = com::unknown_cast<TransMutexScheduler>(&context);
   CUB_ASSERT_VALID_PTR(mutex);

   mutex->unlock(getMutexId());
   waiting = true;

   return CUB_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::final(Status result, TransactionContext& context)
{
   if(!ActionStatus(result).isWorking())
   {
      CUB_ASSERT_SUCC_CALL(unlock(context));
   }

   return result;
}

///////////////////////////////////////////////////////////////////////////////////////////
#define __FINAL(method) final(ROLE(SchedAction).method, context)

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::exec(TransactionContext& context)
{
   ActionStatus status = lock(context);
   if(status.isDone())
   {
     return __FINAL(exec(context));
   }

   return status;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::tryExec(TransactionContext& context, const ev::Event& event)
{
   if(event.matches(EV_MUTEX_UNLOCK))
   {
      TransMutexAvailMsg* msg = (TransMutexAvailMsg*)event.getMsg();
      CUB_ASSERT_VALID_PTR(msg);

      if(msg->matches(getMutexId()))
      {
         event.consume();
         return exec(context);
      }
   }

   return TSL_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return waiting ? tryExec(context, event) : __FINAL(handleEvent(context, event));
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::stop(TransactionContext& context, Status cause)
{
   if(waiting) return cause;

   return __FINAL(stop(context, cause));
}

///////////////////////////////////////////////////////////////////////////////////////////
void   SchedLockAction::kill(TransactionContext& context, Status cause)
{
   if(waiting) return;

   ROLE(SchedAction).kill(context, cause);
   unlock(context);
}

TSL_NS_END

