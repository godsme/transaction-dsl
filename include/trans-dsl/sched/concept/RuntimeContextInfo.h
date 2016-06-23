/*
 * RuntimeContextInfo.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RUNTIMECONTEXTINFO_H_
#define RUNTIMECONTEXTINFO_H_

#include <cub/dci/InterfaceDef.h>
#include <cub/dci/Role.h>
#include <trans-dsl/tsl.h>

TSL_NS_BEGIN

struct RuntimeContext;

UNKNOWN_INTERFACE(RuntimeContextInfo, 973432232)
{
   ABSTRACT(void setRuntimeContext(RuntimeContext&));
   ABSTRACT(RuntimeContext* getRuntimeContext() const);
};

TSL_NS_END

#endif /* RUNTIMECONTEXTINFO_H_ */
