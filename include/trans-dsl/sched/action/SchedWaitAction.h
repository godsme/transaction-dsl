/*
 * SchedWaitAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDWAITACTION_H_
#define SCHEDWAITACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "event/concept/EventId.h"

struct SchedWaitAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   ABSTRACT(EventId getEventId() const);
};

#endif /* SCHEDWAITACTION_H_ */
