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

#include <base/dci/InterfaceDef.h>

struct RuntimeContext;

DEF_INTERFACE(RuntimeContextInfo, 304231933)
{
   ABSTRACT(void setRuntimeContext(RuntimeContext&));
   ABSTRACT(RuntimeContext* getRuntimeContext() const);
};

#endif /* RUNTIMECONTEXTINFO_H_ */
