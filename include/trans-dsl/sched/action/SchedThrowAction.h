/*
 * SchedThrowAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDTHROWACTION_H_
#define SCHEDTHROWACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"

struct SchedThrowAction: SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   ABSTRACT(Status getStatus() const);
};

#endif /* SCHEDTHROWACTION_H_ */
