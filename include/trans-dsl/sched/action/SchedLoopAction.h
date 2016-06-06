/*
 * SchedLoopAction.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDLOOPACTION_H_
#define SCHEDLOOPACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/utils/ActionStatus.h"

struct SchedLoopAction : SchedAction
{
   SchedLoopAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   Status doRestart(TransactionContext&);
   Status restart(TransactionContext&);
   Status doHandleEvent(TransactionContext&, const Event&);
   Status getFinalStatus(const ActionStatus status);
   Status doExec(TransactionContext& context);

private:
   enum
   {
      IDLE,
      EXEC,
      STOPPED
   } state;

   Status stopCause;

private:
   ABSTRACT(bool shouldExecute(TransactionContext&));
   ABSTRACT(void reset());

   USE_ROLE(SchedAction);
};

struct LoopCondCheckAction: FinalAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   ABSTRACT(bool shouldExecute(TransactionContext&) const);
};

#endif /* SCHEDLOOPACTION_H_ */
