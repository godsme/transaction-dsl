/*
 * SchedConcurrentAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDCONCURRENTACTION_H_
#define SCHEDCONCURRENTACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/sched/action/LinkedActionThread.h"
#include "trans-dsl/utils/SimpleRuntimeContext.h"
#include "trans-dsl/utils/ActionStatus.h"
#include <base/utils/List.h>

struct SchedConcurrentAction : private SimpleRuntimeContext, SchedAction
{
   SchedConcurrentAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

   void addThread(LinkedActionThread&);

private:
   Status doExec(TransactionContext& context);
   Status doHandleEvent(TransactionContext&, const Event&);
   Status process(const ActionStatus status,
            TransactionContext& context);
   Status getFinalStatus() const;
   bool hasWorkingThreads() const;
   void doStop(TransactionContext& context, const Status cause);

private:
   typedef List<LinkedActionThread> Threads;
   typedef Threads::Iterator Thread;

   struct AutoSwitch;

private:
   Status doneCheck(const ActionStatus status, Thread& thread);

private:
   Threads threads;
   bool stopping;
};

#endif /* SCHEDCONCURRENTACTION_H_ */
