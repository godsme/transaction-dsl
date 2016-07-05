/*
 * BaseTransactionScheduler.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/sched/trans/BaseTransactionScheduler.h>
#include <trans-dsl/TslStatus.h>

TSL_NS_BEGIN

///////////////////////////////////////////////////////////////////////////////////////
BaseTransactionScheduler::BaseTransactionScheduler(InstanceId iid)
      : SimpleTransactionContext(iid)
{
}

///////////////////////////////////////////////////////////////////////////////////////
BaseTransactionScheduler::BaseTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid)
      : SimpleTransactionContext(runtimeContext, iid)
{
}

///////////////////////////////////////////////////////////////////////////////////////
cub::Status BaseTransactionScheduler::stop(const cub::Status cause)
{
   if(!isWorking()) return TSL_SUCCESS;

   if(inSafeMode()) return TSL_CONTINUE;

   return actualStop(cause);
}

///////////////////////////////////////////////////////////////////////////////////////
void BaseTransactionScheduler::updateInstanceId(InstanceId iid)
{
   SimpleTransactionContext::updateInstanceId(iid);
}

///////////////////////////////////////////////////////////////////////////////////////
void BaseTransactionScheduler::updateTimerInfo(const TimerInfo& info)
{
   SimpleTransactionContext::setTimerInfo(&info);
}

///////////////////////////////////////////////////////////////////////////////////////
void BaseTransactionScheduler::updateTransactionListener(TransactionListener& listener)
{
   SimpleTransactionContext::updateTransactionListener(listener);
}

///////////////////////////////////////////////////////////////////////////////////////
void BaseTransactionScheduler::updateUserContext(com::Unknown* context)
{
   SimpleTransactionContext::updateUserContext(context);
}

///////////////////////////////////////////////////////////////////////////////////////
void BaseTransactionScheduler::updateMutexScheduler(TransMutexScheduler& scheduler)
{
   SimpleTransactionContext::updateMutexScheduler(scheduler);
}

TSL_NS_END


