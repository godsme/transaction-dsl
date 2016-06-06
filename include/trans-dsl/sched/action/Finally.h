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

struct SchedAction;

struct Finally : FinalAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   USE_ROLE(SchedAction);
};

#endif /* FINALLY_H_ */
