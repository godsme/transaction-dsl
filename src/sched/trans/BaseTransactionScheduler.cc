/*
 * BaseTransactionScheduler.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/trans/BaseTransactionScheduler.h"

BaseTransactionScheduler::BaseTransactionScheduler(InstanceId iid)
      : SimpleTransactionContext(iid)
{
}

BaseTransactionScheduler::BaseTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid)
      : SimpleTransactionContext(runtimeContext, iid)
{
}

Status BaseTransactionScheduler::stop(const Status cause)
{
   if(!isWorking()) return SUCCESS;

   if(inSafeMode()) return CONTINUE;

   return actualStop(cause);
}

void BaseTransactionScheduler::updateInstanceId(InstanceId iid)
{
   SimpleTransactionContext::updateInstanceId(iid);
}

void BaseTransactionScheduler::updateTimerInfo(const TimerInfo& info)
{
   SimpleTransactionContext::setTimerInfo(&info);
}

void BaseTransactionScheduler::updateTransactionListener(TransactionListener& listener)
{
   SimpleTransactionContext::updateTransactionListener(listener);
}

void BaseTransactionScheduler::updateUserContext(Unknown* context)
{
   SimpleTransactionContext::updateUserContext(context);
}

void BaseTransactionScheduler::updateMutexScheduler(TransMutexScheduler& scheduler)
{
   SimpleTransactionContext::updateMutexScheduler(scheduler);
}

