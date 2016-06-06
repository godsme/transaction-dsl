/*
 * MultiThreadContext.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADCONTEXT_H_
#define MULTITHREADCONTEXT_H_

#include "trans-dsl/ext/multi-thread/concept/ActionThreadId.h"
#include <base/dci/InterfaceDef.h>
#include <base/Status.h>

struct ActionThread;

DEF_INTERFACE(MultiThreadContext, 304232040)
{
   ABSTRACT(Status startThread(const ActionThreadId, ActionThread&, Status& result));
   ABSTRACT(Status killThread(const ActionThreadId, const Status));
   ABSTRACT(Status stopThread(const ActionThreadId, const Status cause));
   ABSTRACT(Status joinThread(const ActionThreadId, Status& result) const);
};

#endif /* MULTITHREADCONTEXT_H_ */
