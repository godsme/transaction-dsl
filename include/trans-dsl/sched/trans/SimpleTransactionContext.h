/*
 * SimpleTransactionContext.h
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTIONCONTEXT_H_
#define SIMPLETRANSACTIONCONTEXT_H_

#include <trans-dsl/sched/trans/SimpleTransactionInfo.h>
#include <trans-dsl/sched/trans/SimpleRuntimeContextInfo.h>
#include <trans-dsl/utils/AdaptedTimerInfo.h>
#include <trans-dsl/sched/trans/TransactionListenerProxy.h>
#include <trans-dsl/sched/trans/SimpleTransactionMode.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/sched/trans/TransMutexSchedulerAdapter.h>

TSL_NS_BEGIN

struct SimpleTransactionContext
         : protected SimpleTransactionInfo
         , protected TransactionListenerProxy
         , protected SimpleTransactionMode
         , protected AdaptedTimerInfo
         , protected SimpleRuntimeContextInfo
         , protected TransMutexSchedulerAdapter
         , TransactionContext
{
    explicit SimpleTransactionContext(InstanceId iid = 0);
    explicit SimpleTransactionContext(RuntimeContext& runtimeContext, InstanceId iid = 0);

private:
   IMPL_ROLE(TransactionInfo);
   IMPL_ROLE(TransactionListener);
   IMPL_ROLE(TransactionMode);

private:
   IMPL_ROLE(RuntimeContextInfo);

protected:
   BEGIN_INTERFACE_TABLE()
      __HAS_INTERFACE(RuntimeContextInfo)
      __HAS_INTERFACE(TimerInfo)
      __HAS_INTERFACE(TransMutexScheduler)
   END_INTERFACE_TABLE()
};

TSL_NS_END

#endif /* SIMPLETRANSACTIONCONTEXT_H_ */
