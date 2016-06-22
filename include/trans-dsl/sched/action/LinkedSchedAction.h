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
#include <cub/repo/list/ListElem.h>

TSL_NS_BEGIN

struct LinkedSchedAction : SchedAction, cub::ListElem<LinkedSchedAction>
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void        kill(TransactionContext&, const cub::Status));

private:
   USE_ROLE(SchedAction);
};

TSL_NS_END

#endif /* LINKEDSCHEDACTION_H_ */
