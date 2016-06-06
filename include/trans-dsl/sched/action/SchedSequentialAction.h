/*
 * SchedSequentialAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSEQUENTIALACTION_H_
#define SCHEDSEQUENTIALACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/sched/action/LinkedSchedAction.h"
#include "trans-dsl/utils/ActionStatus.h"
#include <base/utils/List.h>

struct SchedSequentialAction: SchedAction
{
   SchedSequentialAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

   void pushBackAction(LinkedSchedAction&);

private:
   Status forward(TransactionContext&);
   Status doHandleEvent(TransactionContext&, const Event&);
   Status getFinalStatus(const ActionStatus, TransactionContext&);
   Status doStop(TransactionContext& context, const Status cause);
   void moveForward();

private:
   typedef List<LinkedSchedAction> Actions;

   SchedAction* current;
   Actions actions;
   Status finalStatus;
};

#endif /* SCHEDSEQUENTIALACTION_H_ */
