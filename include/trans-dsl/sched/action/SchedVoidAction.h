/*
 * SchedVoidAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDVOIDACTION_H_
#define SCHEDVOIDACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"

struct SchedVoidAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   USE_ROLE(SchedAction);
};


#endif /* SCHEDVOIDACTION_H_ */
