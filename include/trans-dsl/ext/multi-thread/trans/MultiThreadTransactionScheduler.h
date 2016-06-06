/*
 * MultiThreadTransactionScheduler.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADTRANSACTIONSCHEDULER_H_
#define MULTITHREADTRANSACTIONSCHEDULER_H_

#include "trans-dsl/ext/multi-thread/trans/MultiThreadScheduler.h"
#include "trans-dsl/sched/trans/BaseTransactionScheduler.h"

struct MultiThreadTransactionScheduler
   : private MultiThreadScheduler
   , BaseTransactionScheduler
{
   explicit MultiThreadTransactionScheduler(const InstanceId iid = 0);

   OVERRIDE(Status start(ActionThread&));
   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(void   kill(const Status));

private:
   OVERRIDE(Status actualStop(const Status));
   OVERRIDE(bool isWorking() const);

private:
   APPEND_INTERFACE_TABLE(BaseTransactionScheduler)
      HAS_INTERFACE(MultiThreadContext)
   END_INTERFACE_TABLE()

private:
   IMPL_ROLE(TransactionContext);
};

#endif /* MULTITHREADTRANSACTIONSCHEDULER_H_ */
