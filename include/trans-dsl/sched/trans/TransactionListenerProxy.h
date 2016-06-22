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

#include <trans-dsl/sched/concept/TransactionListener.h>

TSL_NS_BEGIN

struct TransactionListenerProxy : TransactionListener
{
   TransactionListenerProxy();

   OVERRIDE(void onActionStarting(const ActionId));
   OVERRIDE(void onActionStarted(const ActionId));
   OVERRIDE(void onActionEventConsumed(const ActionId, const ev::Event&));
   OVERRIDE(void onActionDone(const ActionId, const cub::Status result));

   OVERRIDE(void onActionStartStopping(const ActionId, const cub::Status cause));
   OVERRIDE(void onActionStoppingStarted(const ActionId));
   OVERRIDE(void onStoppingEventConsumed(const ActionId, const ev::Event&));
   OVERRIDE(void onActionStopped(const ActionId, const cub::Status result));

   OVERRIDE(void onActionKilled(const ActionId, const cub::Status cause));

   void updateTransactionListener(TransactionListener& listener);

private:
   TransactionListener* listener;
};

TSL_NS_END

#endif /* TRANSACTIONLISTENERPROXY_H_ */
