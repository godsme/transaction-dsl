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

#include "trans-dsl/sched/trans/SimpleTransactionInfo.h"
#include "trans-dsl/sched/trans/SimpleRuntimeContextInfo.h"
#include "trans-dsl/utils/AdaptedTimerInfo.h"
#include "trans-dsl/sched/trans/TransactionListenerProxy.h"
#include "trans-dsl/sched/trans/SimpleTransactionMode.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/sched/trans/TransMutexSchedulerAdapter.h"

#include <base/dci/InterfaceDef.h>

struct SimpleTransactionContext
         : protected SimpleTransactionInfo
         , protected SimpleRuntimeContextInfo
         , protected AdaptedTimerInfo
         , protected TransactionListenerProxy
         , protected SimpleTransactionMode
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
      HAS_INTERFACE(RuntimeContextInfo)
      HAS_INTERFACE(TimerInfo)
      HAS_INTERFACE(TransMutexScheduler)
   END_INTERFACE_TABLE()
};

#endif /* SIMPLETRANSACTIONCONTEXT_H_ */
