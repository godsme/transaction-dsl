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

#include <trans-dsl/sched/concept/FinalAction.h>

TSL_NS_BEGIN

struct SchedAction : FinalAction
{
   ABSTRACT(cub::Status stop(TransactionContext&, const cub::Status cause));
};

TSL_NS_END

#endif /* SCHEDACTION_H_ */
