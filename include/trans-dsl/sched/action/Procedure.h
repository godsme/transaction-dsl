/*
 * Procedure.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PROCEDURE_H_
#define PROCEDURE_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/utils/SimpleRuntimeContext.h"
#include "trans-dsl/utils/DeclState.h"

struct FinalAction;

struct Procedure : private SimpleRuntimeContext, SchedAction
{
   Procedure();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, Status));
   OVERRIDE(void   kill(TransactionContext&, Status));

private:
   OVERRIDE(bool shouldReportParent() const);

private:
   void doKill(FinalAction&, TransactionContext&, Status);
   Status getFinalStatus() const;

private:
   struct State;
   State* state;

   struct AutoSwitch;

private:
   __DECL_STATE(Idle);
   __DECL_STATE(Working);
   __DECL_STATE(Stopping);
   __DECL_STATE(Final);
   __DECL_STATE(Done);

   struct WorkingState;

private:
   USE_ROLE(SchedAction);
   USE_ROLE(FinalAction);
   ABSTRACT(bool isProtected() const);
};

#endif /* PROCEDURE_H_ */
