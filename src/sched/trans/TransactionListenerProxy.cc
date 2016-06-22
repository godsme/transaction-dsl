/*
 * TransactionListenerProxy.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/sched/trans/TransactionListenerProxy.h>

TSL_NS_BEGIN

namespace
{
   TransactionListener* getNullListener()
   {
      static TransactionListener nullListener;
      return &nullListener;
   }
}

TransactionListenerProxy::TransactionListenerProxy()
  : listener(getNullListener())
{
}

void TransactionListenerProxy::onActionStarting(const ActionId id)
{
   listener->onActionStarting(id);
}

void TransactionListenerProxy::onActionStarted(const ActionId id)
{
   listener->onActionStarted(id);
}

void TransactionListenerProxy::onActionEventConsumed(const ActionId id, const ev::Event& event)
{
   listener->onActionEventConsumed(id, event);
}

void TransactionListenerProxy::onActionDone(const ActionId id, const cub::Status result)
{
   listener->onActionDone(id, result);
}

void TransactionListenerProxy::onActionStartStopping(const ActionId id, const cub::Status cause)
{
   listener->onActionStartStopping(id, cause);
}

void TransactionListenerProxy::onActionStoppingStarted(const ActionId id)
{
   listener->onActionStoppingStarted(id);
}

void TransactionListenerProxy::onStoppingEventConsumed(const ActionId id, const ev::Event& event)
{
   listener->onStoppingEventConsumed(id, event);
}

void TransactionListenerProxy::onActionStopped(const ActionId id, const cub::Status result)
{
   listener->onActionStopped(id, result);
}

void TransactionListenerProxy::onActionKilled(const ActionId id, const cub::Status cause)
{
   listener->onActionKilled(id, cause);
}

void TransactionListenerProxy::updateTransactionListener(TransactionListener& listener)
{
   this->listener = &listener;
}

TSL_NS_END

