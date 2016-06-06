/*
 * ActionThread.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONTHREAD_H_
#define ACTIONTHREAD_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/utils/SimpleRuntimeContext.h"
#include "trans-dsl/utils/DeclState.h"

struct ActionThread : private SimpleRuntimeContext, SchedAction
{
   ActionThread();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

   using SimpleRuntimeContext::getStatus;

   bool isWorking() const;

private:
   struct State;
   State* state;

   struct WorkingState;

private:
   __DECL_STATE(Idle);
   __DECL_STATE(Working);
   __DECL_STATE(Stopping);
   __DECL_STATE(Done);

   struct AutoSwitch;

private:
   USE_ROLE(SchedAction);
};

#endif /* ACTIONTHREAD_H_ */
