/*
 * RuntimeContextAutoSwitch.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RUNTIMECONTEXTAUTOSWITCH_H_
#define RUNTIMECONTEXTAUTOSWITCH_H_

#include <trans-dsl/tsl.h>

TSL_NS_BEGIN

struct RuntimeContextInfo;
struct RuntimeContext;
struct TransactionContext;

struct RuntimeContextAutoSwitch
{
   RuntimeContextAutoSwitch
        ( RuntimeContext& newRuntimeContext
        , RuntimeContext*& parentKeeper
        , TransactionContext& context);

   ~RuntimeContextAutoSwitch();

private:
   RuntimeContext*& parentKeeper;
   RuntimeContextInfo* contextInfo;
};

TSL_NS_END

#endif /* RUNTIMECONTEXTAUTOSWITCH_H_ */
