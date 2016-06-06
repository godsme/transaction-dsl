/*
 * Action.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTION_H_
#define ACTION_H_

#include "trans-dsl/action/SyncAction.h"

struct Event;

struct Action : SyncAction
{
   ABSTRACT(Status handleEvent(const TransactionInfo&, const Event&));
   ABSTRACT(void   kill(const TransactionInfo&, const Status cause));
};

#endif /* ACTION_H_ */
