/*
 * SimpleRuntimeContextInfo.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */


#include <trans-dsl/sched/trans/SimpleRuntimeContextInfo.h>

TSL_NS_BEGIN

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

TSL_NS_END
