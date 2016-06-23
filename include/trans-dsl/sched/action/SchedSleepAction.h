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

#include <trans-dsl/sched/concept/SchedAction.h>

TSL_NS_BEGIN

struct RelativeTimer;

struct SchedSleepAction : SchedAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   USE_ROLE(RelativeTimer);
};

TSL_NS_END

#endif /* SCHEDSLEEPACTION_H_ */
