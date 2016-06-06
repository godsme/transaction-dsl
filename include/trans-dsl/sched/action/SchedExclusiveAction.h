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
#include <base/utils/List.h>

struct SchedExclusiveAction : SchedAction
{
   SchedExclusiveAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

   void addAction(LinkedSchedAction&);

private:
   Status selectAction(TransactionContext&, const Event&);
   void interruptOthers(TransactionContext&);

private:
   typedef List<LinkedSchedAction> Actions;

   Actions actions;
   SchedAction* selectedAction;
};

#endif /* SCHEDEXCLUSIVEACTION_H_ */
