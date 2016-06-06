/*
 * UserActionListener.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef USERACTIONLISTENER_H_
#define USERACTIONLISTENER_H_

#include "trans-dsl/sched/concept/ActionId.h"
#include <base/dci/Role.h>
#include <base/Status.h>

struct Event;

DEFINE_ROLE(UserActionListener)
{
   DEFAULT(void, onActionStarting(const ActionId));
   DEFAULT(void, onActionStarted(const ActionId));
   DEFAULT(void, onActionEventConsumed(const ActionId, const Event&));
   DEFAULT(void, onActionDone(const ActionId, const Status));

   DEFAULT(void, onActionKilled(const ActionId, const Status));
};

#endif /* USERACTIONLISTENER_H_ */
