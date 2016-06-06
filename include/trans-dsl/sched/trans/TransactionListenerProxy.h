/*
 * TransactionListenerProxy.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONLISTENERPROXY_H_
#define TRANSACTIONLISTENERPROXY_H_

#include "trans-dsl/sched/concept/TransactionListener.h"

struct TransactionListenerProxy : TransactionListener
{
   TransactionListenerProxy();

   OVERRIDE(void onActionStarting(const ActionId));
   OVERRIDE(void onActionStarted(const ActionId));
   OVERRIDE(void onActionEventConsumed(const ActionId, const Event&));
   OVERRIDE(void onActionDone(const ActionId, const Status result));

   OVERRIDE(void onActionStartStopping(const ActionId, const Status cause));
   OVERRIDE(void onActionStoppingStarted(const ActionId));
   OVERRIDE(void onStoppingEventConsumed(const ActionId, const Event&));
   OVERRIDE(void onActionStopped(const ActionId, const Status result));

   OVERRIDE(void onActionKilled(const ActionId, const Status cause));

   void updateTransactionListener(TransactionListener& listener);

private:
   TransactionListener* listener;
};

#endif /* TRANSACTIONLISTENERPROXY_H_ */
