/*
 * SimpleAsyncAction.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLEASYNCACTION_H_
#define SIMPLEASYNCACTION_H_

#include "trans-dsl/action/Action.h"
#include "trans-dsl/utils/EventHandlerRegistry.h"

struct SimpleAsyncAction: Action
{
   OVERRIDE(Status handleEvent(const TransactionInfo&, const Event&));
   OVERRIDE(void kill(const TransactionInfo&, const Status));

   template<typename T>
   Status waitOn(const EventId eventId, T* thisPointer,
            Status (T::*handler)(const TransactionInfo&, const Event&), bool forever = false)
   {
      return registry.addHandler(eventId, thisPointer, handler, forever);
   }

   Status waitUntouchEvent(const EventId eventId);

private:
   EventHandlerRegistry registry;

public:
   ABSTRACT(Status exec(const TransactionInfo&));

private:
   DEFAULT(void, doKill(const TransactionInfo&, const Status));
};

#endif /* SIMPLEASYNCACTION_H_ */
