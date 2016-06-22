/*
 * SimpleRuntimeContext.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLERUNTIMECONTEXT_H_
#define SIMPLERUNTIMECONTEXT_H_

#include <trans-dsl/sched/concept/RuntimeContext.h>

TSL_NS_BEGIN

struct SimpleRuntimeContext : RuntimeContext
{
   explicit SimpleRuntimeContext(cub::Status parentStatus = TSL_SUCCESS);

   OVERRIDE(void reportFailure(cub::Status));
   OVERRIDE(cub::Status getStatus() const);

protected:
   RuntimeContext* parent;
   cub::Status objectStatus;

private:
   virtual bool shouldReportParent() const { return true; }
};

TSL_NS_END

#endif /* SIMPLERUNTIMECONTEXT_H_ */
