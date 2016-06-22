/*
 * SchedExclusiveAction.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDEXCLUSIVEACTION_H_
#define SCHEDEXCLUSIVEACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/sched/action/LinkedSchedAction.h"
#include <cub/repo/list/List.h>

TSL_NS_BEGIN

struct SchedExclusiveAction : SchedAction
{
   SchedExclusiveAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void   kill(TransactionContext&, const cub::Status));

   void addAction(LinkedSchedAction&);

private:
   cub::Status selectAction(TransactionContext&, const ev::Event&);
   void interruptOthers(TransactionContext&);

private:
   typedef cub::List<LinkedSchedAction> Actions;

   Actions actions;
   SchedAction* selectedAction;
};

TSL_NS_END

#endif /* SCHEDEXCLUSIVEACTION_H_ */
