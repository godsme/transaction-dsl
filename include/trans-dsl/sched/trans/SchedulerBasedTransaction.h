/*
 * SchedulerBasedTransaction.h
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDULERBASEDTRANSACTION_H_
#define SCHEDULERBASEDTRANSACTION_H_

#include "trans-dsl/sched/trans/SchedTransaction.h"

TSL_NS_BEGIN

template <typename T_SCHEDULER>
struct SchedulerBasedTransaction : SchedTransaction
{
   SchedulerBasedTransaction(InstanceId iid = 0)
      : scheduler(iid) {}

private:
   ROLE_PROTO_TYPE(TransactionScheduler)
   {
      return scheduler;
   }

   mutable T_SCHEDULER scheduler;

private:
   USE_ROLE(ActionThread);
};

TSL_NS_END

#endif /* SCHEDULERBASEDTRANSACTION_H_ */
