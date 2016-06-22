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

#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/sched/concept/ActionId.h>
#include <trans-dsl/utils/DeclState.h>

TSL_NS_BEGIN

struct SchedWithIdAction : SchedAction
{
   SchedWithIdAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

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

TSL_NS_END

#endif /* SCHEDWITHIDACTION_H_ */
