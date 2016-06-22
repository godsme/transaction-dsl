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
#include <cub/repo/list/List.h>

TSL_NS_BEGIN

struct SchedConcurrentAction : private SimpleRuntimeContext, SchedAction
{
   SchedConcurrentAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

   void addThread(LinkedActionThread&);

private:
   cub::Status doExec(TransactionContext& context);
   cub::Status doHandleEvent(TransactionContext&, const ev::Event&);
   cub::Status process(const ActionStatus status,
            TransactionContext& context);
   cub::Status getFinalStatus() const;
   bool hasWorkingThreads() const;
   void doStop(TransactionContext& context, const cub::Status cause);

private:
   typedef cub::List<LinkedActionThread> Threads;
   typedef Threads::Iterator Thread;

   struct AutoSwitch;

private:
   cub::Status doneCheck(const ActionStatus status, Thread& thread);

private:
   Threads threads;
   bool stopping;
};

TSL_NS_END

#endif /* SCHEDCONCURRENTACTION_H_ */
