/*
 * SchedSwitchCaseAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSWITCHCASEACTION_H_
#define SCHEDSWITCHCASEACTION_H_

#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/sched/action/ActionPath.h>
#include <cub/repo/list/List.h>

TSL_NS_BEGIN

struct SchedSwitchCaseAction : SchedAction
{
   SchedSwitchCaseAction();

   OVERRIDE(cub::Status exec(TransactionContext& context));
   OVERRIDE(cub::Status handleEvent(TransactionContext& context, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void   kill(TransactionContext&, const cub::Status));

   void pushBackActionPath(ActionPath& listener);

private:
   SchedAction* findMatchedAction(TransactionContext&);

private:
   typedef cub::List<ActionPath> Paths;

   Paths          paths;
   SchedAction*   selectedAction;
};

TSL_NS_END

#endif /* SCHEDSWITCHCASEACTION_H_ */
