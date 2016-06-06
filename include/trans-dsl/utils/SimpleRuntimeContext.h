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

#include "trans-dsl/sched/concept/RuntimeContext.h"

struct SimpleRuntimeContext : RuntimeContext
{
   explicit SimpleRuntimeContext(Status parentStatus = SUCCESS);

   OVERRIDE(void reportFailure(Status));
   OVERRIDE(Status getStatus() const);

protected:
   RuntimeContext* parent;
   Status objectStatus;

private:
   virtual bool shouldReportParent() const { return true; }
};

#endif /* SIMPLERUNTIMECONTEXT_H_ */
