/*
 * SchedAction.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDACTION_H_
#define SCHEDACTION_H_

#include "trans-dsl/sched/concept/FinalAction.h"

struct SchedAction : FinalAction
{
   ABSTRACT(Status stop(TransactionContext&, const Status cause));
};


#endif /* SCHEDACTION_H_ */
