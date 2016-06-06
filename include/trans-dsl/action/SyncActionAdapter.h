/*
 * SyncActionAdapter.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SYNCACTIONADAPTER_H_
#define SYNCACTIONADAPTER_H_

#include "trans-dsl/action/Action.h"

struct SyncActionAdapter: Action
{
private:
   OVERRIDE(Status exec(const TransactionInfo&));
   OVERRIDE(Status handleEvent(const TransactionInfo&, const Event&));
   OVERRIDE(void   kill(const TransactionInfo&, const Status cause));

private:
   USE_ROLE(SyncAction);
};

#endif /* SYNCACTIONADAPTER_H_ */
