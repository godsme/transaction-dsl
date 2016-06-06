/*
 * SimpleTransactionContext.cc
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/trans/SimpleTransactionContext.h"

SimpleTransactionContext::SimpleTransactionContext(InstanceId iid)
  : SimpleTransactionInfo(iid)
{
}

SimpleTransactionContext::SimpleTransactionContext(RuntimeContext& runtimeContext, InstanceId iid )
  : SimpleTransactionInfo(iid)
  , SimpleRuntimeContextInfo(runtimeContext)
{

}
