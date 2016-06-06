/*
 * SimpleRuntimeContextInfo.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */


#include "trans-dsl/sched/trans/SimpleRuntimeContextInfo.h"

SimpleRuntimeContextInfo::SimpleRuntimeContextInfo()
   : runtimeContext(0)
{
}

SimpleRuntimeContextInfo::SimpleRuntimeContextInfo(RuntimeContext& runtimeContext)
   : runtimeContext(&runtimeContext)
{
}

void SimpleRuntimeContextInfo::setRuntimeContext(RuntimeContext& context)
{
   runtimeContext = &context;
}

RuntimeContext* SimpleRuntimeContextInfo::getRuntimeContext() const
{
   return runtimeContext;
}
