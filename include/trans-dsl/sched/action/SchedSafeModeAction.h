/*
 * SchedSafeModeAction.h
 *
 * Created on: Jun 10, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSAFEMODEACTION_H_
#define SCHEDSAFEMODEACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"

TSL_NS_BEGIN

struct SchedSafeModeAction : SchedAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
   OVERRIDE(void kill(TransactionContext&, const cub::Status));

private:
   cub::Status final(TransactionContext& context, cub::Status status);

private:
   USE_ROLE(SchedAction);
};

TSL_NS_END

#endif /* SCHEDSAFEMODEACTION_H_ */
