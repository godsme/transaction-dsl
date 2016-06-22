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

#include <trans-dsl/sched/concept/SchedAction.h>

TSL_NS_BEGIN

struct Action;

///////////////////////////////////////////////////////////////
struct SchedActionAdapter: SchedAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   USE_ROLE(Action);
};

TSL_NS_END

#endif /* SCHEDACTIONADAPTER_H_ */
