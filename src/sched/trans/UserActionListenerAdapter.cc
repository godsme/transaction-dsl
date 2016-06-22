/*
 * UserActionListenerAdapter.cc
 *
 * Created on: May 29, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/trans/UserActionListenerAdapter.h"
#include "trans-dsl/sched/concept/UserActionListener.h"

void UserActionListenerAdapter::onActionStarting(const ActionId id)
{
   ROLE(UserActionListener).onActionStarting(id);
}

void UserActionListenerAdapter::onActionStarted(const ActionId id)
{
   ROLE(UserActionListener).onActionStarted(id);
}

void UserActionListenerAdapter::onActionEventConsumed(const ActionId id, const Event& event)
{
   ROLE(UserActionListener).onActionEventConsumed(id, event);
}

void UserActionListenerAdapter::onActionDone(const ActionId id, const Status result)
{
   ROLE(UserActionListener).onActionDone(id, result);
}

void UserActionListenerAdapter::onActionStartStopping(const ActionId id, const Status cause)
{
   ROLE(UserActionListener).onActionKilled(id, cause);
}

void UserActionListenerAdapter::onActionStoppingStarted(const ActionId id)
{
}

void UserActionListenerAdapter::onStoppingEventConsumed(const ActionId id, const Event& event)
{
}

void UserActionListenerAdapter::onActionStopped(const ActionId id, const Status result)
{
}

void UserActionListenerAdapter::onActionKilled(const ActionId id, const Status cause)
{
   ROLE(UserActionListener).onActionKilled(id, cause);
}
