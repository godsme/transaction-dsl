/*
 * TransactionListener.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONLISTENER_H_
#define TRANSACTIONLISTENER_H_

#include "trans-dsl/sched/concept/ActionId.h"
#include <base/dci/Role.h>
#include <base/Status.h>
#include <base/Default.h>

struct Event;

DEFINE_ROLE(TransactionListener)
{
   DEFAULT(void, onActionStarting(const ActionId));
   DEFAULT(void, onActionStarted(const ActionId));
   DEFAULT(void, onActionEventConsumed(const ActionId, const Event&));
   DEFAULT(void, onActionDone(const ActionId, const Status));

   DEFAULT(void, onActionStartStopping(const ActionId, const Status));
   DEFAULT(void, onActionStoppingStarted(const ActionId));
   DEFAULT(void, onStoppingEventConsumed(const ActionId, const Event&));
   DEFAULT(void, onActionStopped(const ActionId, const Status));

   DEFAULT(void, onActionKilled(const ActionId, const Status));
};

#endif /* TRANSACTIONLISTENER_H_ */
