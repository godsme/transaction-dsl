/*
 * SimpleRuntimeContextAutoSwitch.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLERUNTIMECONTEXTAUTOSWITCH_H_
#define SIMPLERUNTIMECONTEXTAUTOSWITCH_H_

#include <trans-dsl/utils/RuntimeContextAutoSwitch.h>

TSL_NS_BEGIN

struct SimpleRuntimeContextAutoSwitch : RuntimeContextAutoSwitch
{
   SimpleRuntimeContextAutoSwitch
        ( RuntimeContext& newRuntimeContext
        , TransactionContext& context)
        : RuntimeContextAutoSwitch(newRuntimeContext, parent, context)
   {
   }

private:
   RuntimeContext* parent;
};

TSL_NS_END

#endif /* SIMPLERUNTIMECONTEXTAUTOSWITCH_H_ */
