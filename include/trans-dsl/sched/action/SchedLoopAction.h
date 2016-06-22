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

TSL_NS_BEGIN

struct SchedLoopAction : SchedAction
{
   SchedLoopAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   cub::Status doRestart(TransactionContext&);
   cub::Status restart(TransactionContext&);
   cub::Status doHandleEvent(TransactionContext&, const ev::Event&);
   cub::Status getFinalStatus(const ActionStatus status);
   cub::Status doExec(TransactionContext& context);

private:
   enum
   {
      IDLE,
      EXEC,
      STOPPED
   } state;

   cub::Status stopCause;

private:
   ABSTRACT(bool shouldExecute(TransactionContext&));
   ABSTRACT(void reset());

   USE_ROLE(SchedAction);
};

struct LoopCondCheckAction: FinalAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   ABSTRACT(bool shouldExecute(TransactionContext&) const);
};

TSL_NS_END

#endif /* SCHEDLOOPACTION_H_ */
