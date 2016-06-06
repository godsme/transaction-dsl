/*
 * SchedPeekAction.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDPEEKACTION_H_
#define SCHEDPEEKACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "event/concept/EventId.h"

struct SchedPeekAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   ABSTRACT(EventId getEventId() const);
};

#endif /* SCHEDPEEKACTION_H_ */
