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

#include <trans-dsl/ext/multi-thread/concept/ActionThreadId.h>

#include <cub/dci/Role.h>
#include <cub/base/Status.h>
#include <cub/dci/InterfaceDef.h>

TSL_NS_BEGIN

struct ActionThread;

UNKNOWN_INTERFACE(MultiThreadContext, 304232040)
{
   ABSTRACT(cub::Status startThread(const ActionThreadId, ActionThread&, cub::Status& result));
   ABSTRACT(cub::Status killThread(const ActionThreadId, const cub::Status));
   ABSTRACT(cub::Status stopThread(const ActionThreadId, const cub::Status cause));
   ABSTRACT(cub::Status joinThread(const ActionThreadId, cub::Status& result) const);
};

TSL_NS_END

#endif /* MULTITHREADCONTEXT_H_ */
