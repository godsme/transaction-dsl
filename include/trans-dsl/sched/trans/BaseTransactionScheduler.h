/*
 * BaseTransactionScheduler.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef BASETRANSACTIONSCHEDULER_H_
#define BASETRANSACTIONSCHEDULER_H_

#include <trans-dsl/sched/trans/SimpleTransactionContext.h>
#include <trans-dsl/sched/concept/TransactionScheduler.h>

TSL_NS_BEGIN

struct BaseTransactionScheduler
         : SimpleTransactionContext
         , TransactionScheduler
{
   explicit BaseTransactionScheduler(InstanceId iid = 0);
   explicit BaseTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid = 0);

   OVERRIDE(void updateInstanceId(InstanceId iid));
   OVERRIDE(void updateTimerInfo(const TimerInfo&));
   OVERRIDE(void updateTransactionListener(TransactionListener&));
   OVERRIDE(void updateUserContext(com::Unknown*));
   OVERRIDE(void updateMutexScheduler(TransMutexScheduler&));

   OVERRIDE(cub::Status stop(const cub::Status));

private:
   ABSTRACT(cub::Status actualStop(const cub::Status));
   ABSTRACT(bool isWorking() const);
};

TSL_NS_END

#endif /* BASETRANSACTIONSCHEDULER_H_ */
