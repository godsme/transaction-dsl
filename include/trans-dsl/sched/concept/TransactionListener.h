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

#include <trans-dsl/sched/concept/ActionId.h>

#include <cub/base/Default.h>
#include <cub/base/Status.h>
#include <cub/dci/Role.h>
#include <event/event.h>

FWD_DECL_EV(Event)

TSL_NS_BEGIN

DEFINE_ROLE(TransactionListener)
{
   DEFAULT(void, onActionStarting(const ActionId));
   DEFAULT(void, onActionStarted(const ActionId));
   DEFAULT(void, onActionEventConsumed(const ActionId, const ev::Event&));
   DEFAULT(void, onActionDone(const ActionId, const cub::Status));

   DEFAULT(void, onActionStartStopping(const ActionId, const cub::Status));
   DEFAULT(void, onActionStoppingStarted(const ActionId));
   DEFAULT(void, onStoppingEventConsumed(const ActionId, const ev::Event&));
   DEFAULT(void, onActionStopped(const ActionId, const cub::Status));

   DEFAULT(void, onActionKilled(const ActionId, const cub::Status));
};

TSL_NS_END

#endif /* TRANSACTIONLISTENER_H_ */
