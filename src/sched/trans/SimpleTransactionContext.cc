/*
 * SimpleTransactionContext.cc
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/sched/trans/SimpleTransactionContext.h>

TSL_NS_BEGIN

SimpleTransactionContext::SimpleTransactionContext(InstanceId iid)
  : SimpleTransactionInfo(iid)
{
}

SimpleTransactionContext::SimpleTransactionContext(RuntimeContext& runtimeContext, InstanceId iid )
  : SimpleTransactionInfo(iid)
  , SimpleRuntimeContextInfo(runtimeContext)
{

}

TSL_NS_END

