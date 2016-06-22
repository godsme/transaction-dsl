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

TSL_NS_BEGIN

struct SimpleAsyncAction: Action
{
   OVERRIDE(cub::Status handleEvent(const TransactionInfo&, const ev::Event&));
   OVERRIDE(void kill(const TransactionInfo&, const cub::Status));

   template<typename T>
   cub::Status waitOn(const ev::EventId eventId, T* thisPointer,
		   cub::Status (T::*handler)(const TransactionInfo&, const ev::Event&), bool forever = false)
   {
      return registry.addHandler(eventId, thisPointer, handler, forever);
   }

   cub::Status waitUntouchEvent(const ev::EventId eventId);

private:
   EventHandlerRegistry registry;

public:
   ABSTRACT(cub::Status exec(const TransactionInfo&));

private:
   DEFAULT(void, doKill(const TransactionInfo&, const cub::Status));
};

TSL_NS_END

#endif /* SIMPLEASYNCACTION_H_ */
