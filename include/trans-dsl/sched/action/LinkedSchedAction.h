/*
 * LinkedSchedAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDSCHEDACTION_H_
#define LINKEDSCHEDACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include <base/utils/ListElem.h>

struct LinkedSchedAction : SchedAction, ListElem<LinkedSchedAction>
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   USE_ROLE(SchedAction);
};

#endif /* LINKEDSCHEDACTION_H_ */
