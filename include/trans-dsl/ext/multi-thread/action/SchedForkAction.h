/*
 * SchedForkAction.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDFORKACTION_H_
#define SCHEDFORKACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"
#include "trans-dsl/ext/multi-thread/concept/ActionThreadId.h"

struct ActionThread;

struct SchedForkAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, Status));
   OVERRIDE(void   kill(TransactionContext&, Status));

private:
   USE_ROLE(ActionThread);
   ABSTRACT(ActionThreadId getThreadId() const);
};

#endif /* SCHEDFORKACTION_H_ */
