/*
 * SimpleTransactionScheduler.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#ifndef SIMPLETRANSACTIONSCHEDULER_H_
#define SIMPLETRANSACTIONSCHEDULER_H_

#include "trans-dsl/sched/trans/BaseTransactionScheduler.h"
#include "trans-dsl/sched/trans/SimpleTransactionContext.h"

TSL_NS_BEGIN

struct SimpleTransactionScheduler
   : BaseTransactionScheduler
{
   explicit SimpleTransactionScheduler(InstanceId iid = 0);
   explicit SimpleTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid = 0);

   OVERRIDE(cub::Status start(ActionThread&));
   OVERRIDE(cub::Status handleEvent(const ev::Event&));
   OVERRIDE(void   kill(const cub::Status));

private:
   OVERRIDE(cub::Status actualStop(const cub::Status));
   OVERRIDE(bool isWorking() const);

private:
   ActionThread* thread;
};

TSL_NS_END

#endif /* SIMPLETRANSACTIONSCHEDULER_H_ */
