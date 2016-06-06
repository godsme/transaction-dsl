/*
 * SchedActionAdapter.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDACTIONADAPTER_H_
#define SCHEDACTIONADAPTER_H_

#include "trans-dsl/sched/concept/SchedAction.h"

struct Action;

///////////////////////////////////////////////////////////////
struct SchedActionAdapter: SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   USE_ROLE(Action);
};

#endif /* SCHEDACTIONADAPTER_H_ */
