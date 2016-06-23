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

#include <cub/repo/list/List.h>
#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/sched/action/LinkedSchedAction.h>
#include <trans-dsl/utils/ActionStatus.h>

TSL_NS_BEGIN

struct SchedSequentialAction: SchedAction
{
   SchedSequentialAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

   void pushBackAction(LinkedSchedAction&);

private:
   cub::Status forward(TransactionContext&);
   cub::Status doHandleEvent(TransactionContext&, const ev::Event&);
   cub::Status getFinalStatus(const ActionStatus, TransactionContext&);
   cub::Status doStop(TransactionContext& context, const cub::Status cause);
   void moveForward();

private:
   typedef cub::List<LinkedSchedAction> Actions;

   SchedAction* current;
   Actions actions;
   cub::Status finalStatus;
};

TSL_NS_END

#endif /* SCHEDSEQUENTIALACTION_H_ */
