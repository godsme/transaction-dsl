/*
 * SimpleAsyncAction.cc
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/action/SimpleAsyncAction.h"

using namespace cub;
using namespace ev;

TSL_NS_BEGIN

//////////////////////////////////////////////////////////////////////
Status SimpleAsyncAction::handleEvent(const TransactionInfo& trans, const ev::Event& event)
{
   typedef Status (DummyEventHandlerClass::*Handler)(const TransactionInfo&, const ev::Event&);

   struct Executer: EventHandlerExecuter
{
      Executer(const TransactionInfo& trans) :
               trans(trans)
      {
      }

      Status exec(const ev::Event& event, DummyEventHandlerClass* thisClass, DummyEventHandler handler)
      {
         Handler actualHandler = reinterpret_cast<Handler>(handler);
         return (thisClass->*actualHandler)(trans, event);
      }

   private:
      const TransactionInfo& trans;
   }
   executor(trans);

   return registry.handleEvent(event, executor);
}

//////////////////////////////////////////////////////////////////////
Status SimpleAsyncAction::waitUntouchEvent(const ev::EventId eventId)
{
   return registry.addUntouchedEvent(eventId);
}

//////////////////////////////////////////////////////////////////////
void SimpleAsyncAction::kill(const TransactionInfo& trans, const Status cause)
{
   registry.reset();
   doKill(trans, cause);
}

TSL_NS_END

