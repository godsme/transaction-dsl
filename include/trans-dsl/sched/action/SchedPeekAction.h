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

TSL_NS_BEGIN

struct SchedPeekAction : SchedAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   ABSTRACT(ev::EventId getEventId() const);
};

TSL_NS_END

#endif /* SCHEDPEEKACTION_H_ */
