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

#include <trans-dsl/ext/multi-thread/trans/MultiThreadScheduler.h>
#include <trans-dsl/sched/trans/BaseTransactionScheduler.h>

TSL_NS_BEGIN

struct MultiThreadTransactionScheduler
   : MultiThreadScheduler
   , BaseTransactionScheduler
{
   explicit MultiThreadTransactionScheduler(const InstanceId iid = 0);

   OVERRIDE(cub::Status start(ActionThread&));
   OVERRIDE(cub::Status handleEvent(const ev::Event&));
   OVERRIDE(void   kill(const cub::Status));

private:
   OVERRIDE(cub::Status actualStop(const cub::Status));
   OVERRIDE(bool isWorking() const);

private:
   IMPL_ROLE(TransactionContext);

   APPEND_INTERFACE_TABLE(BaseTransactionScheduler)
      __HAS_INTERFACE(MultiThreadContext)
   END_INTERFACE_TABLE()
};

TSL_NS_END

#endif /* MULTITHREADTRANSACTIONSCHEDULER_H_ */
