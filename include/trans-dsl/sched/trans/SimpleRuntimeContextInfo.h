/*
 * SimpleRuntimeContextInfo.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLERUNTIMECONTEXTINFO_H_
#define SIMPLERUNTIMECONTEXTINFO_H_

#include <trans-dsl/sched/concept/RuntimeContextInfo.h>

TSL_NS_BEGIN

struct SimpleRuntimeContextInfo : RuntimeContextInfo
{
   SimpleRuntimeContextInfo();
   explicit SimpleRuntimeContextInfo(RuntimeContext& runtimeContext);

   void setRuntimeContext(RuntimeContext&);
   RuntimeContext* getRuntimeContext() const;

private:
   RuntimeContext* runtimeContext;
};

TSL_NS_END

#endif /* SIMPLERUNTIMECONTEXTINFO_H_ */
