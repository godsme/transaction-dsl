/*
 * NilFinalAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef NILFINALACTION_H_
#define NILFINALACTION_H_

#include "trans-dsl/sched/concept/FinalAction.h"

struct NilFinalAction : FinalAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(void   kill(TransactionContext&, const Status));
};

#endif /* NILFINALACTION_H_ */
