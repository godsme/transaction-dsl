/*
 * SchedSleepAction.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSLEEPACTION_H_
#define SCHEDSLEEPACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"

struct RelativeTimer;

struct SchedSleepAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   USE_ROLE(RelativeTimer);
};

#endif /* SCHEDSLEEPACTION_H_ */
