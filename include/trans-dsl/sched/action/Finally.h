/*
 * Finally.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FINALLY_H_
#define FINALLY_H_

#include "trans-dsl/sched/concept/FinalAction.h"

TSL_NS_BEGIN

struct SchedAction;

struct Finally : FinalAction
{
   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(void   kill(TransactionContext&, const cub::Status));

private:
   USE_ROLE(SchedAction);
};

TSL_NS_END

#endif /* FINALLY_H_ */
