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

#include "trans-dsl/sched/trans/SimpleTransactionContext.h"
#include "trans-dsl/sched/concept/TransactionScheduler.h"

struct BaseTransactionScheduler
         : protected SimpleTransactionContext
         , TransactionScheduler
{
   explicit BaseTransactionScheduler(InstanceId iid = 0);
   explicit BaseTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid = 0);

   OVERRIDE(void updateInstanceId(InstanceId iid));
   OVERRIDE(void updateTimerInfo(const TimerInfo&));
   OVERRIDE(void updateTransactionListener(TransactionListener&));
   OVERRIDE(void updateUserContext(Unknown*));
   OVERRIDE(void updateMutexScheduler(TransMutexScheduler&));

   OVERRIDE(Status stop(const Status));

private:
   ABSTRACT(Status actualStop(const Status));
   ABSTRACT(bool isWorking() const);
};

#endif /* BASETRANSACTIONSCHEDULER_H_ */
