/*
 * SchedWithIdAction.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDWITHIDACTION_H_
#define SCHEDWITHIDACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/sched/concept/ActionId.h"
#include "trans-dsl/utils/DeclState.h"

struct SchedWithIdAction : SchedAction
{
   SchedWithIdAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   struct State;
   State* state;

private:
   __DECL_STATE(Idle);
   __DECL_STATE(Working);
   __DECL_STATE(Stopping);
   __DECL_STATE(Done);

private:
   ABSTRACT(ActionId getActionId() const);
   USE_ROLE(SchedAction);
};

#endif /* SCHEDWITHIDACTION_H_ */
