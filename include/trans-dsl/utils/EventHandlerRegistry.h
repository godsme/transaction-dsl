/*
 * EventHandlerRegistry.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef EVENTHANDLERREGISTRY_H_
#define EVENTHANDLERREGISTRY_H_

#include <cub/dci/Role.h>
#include <cub/base/Status.h>
#include <cub/mem/Placement.h>

#include <event/concept/EventId.h>
#include <trans-dsl/tsl.h>

FWD_DECL_EV(Event);

TSL_NS_BEGIN

///////////////////////////////////////////////////////////////
struct DummyEventHandlerClass
{
   void dummy()
   {
   }
};

///////////////////////////////////////////////////////////////
typedef void (DummyEventHandlerClass::*DummyEventHandler)();

///////////////////////////////////////////////////////////////
DEFINE_ROLE(EventHandlerExecuter)
{
   ABSTRACT(cub::Status exec(const ev::Event&, DummyEventHandlerClass*, DummyEventHandler));
};

///////////////////////////////////////////////////////////////
struct EventHandlerRegistry
{
   template<typename T, typename HANDLER>
   cub::Status addHandler(const ev::EventId eventId, T* thisPointer, HANDLER handler, bool forever = false)
   {
      return doAddHandler
               ( eventId
               , (DummyEventHandlerClass*) thisPointer
               , (DummyEventHandler) handler
               , forever);
   }

   cub::Status addUntouchedEvent(const ev::EventId eventId);

   cub::Status handleEvent(const ev::Event&, EventHandlerExecuter&);

   void reset();

private:
   cub::Status doAddHandler(const ev::EventId, DummyEventHandlerClass*,
            DummyEventHandler, bool forever);

   void clear();
private:

   struct EventHandler
   {
      EventHandler(const ev::EventId, DummyEventHandlerClass*, DummyEventHandler);
      EventHandler(const ev::EventId);
      EventHandler(const EventHandler& rhs);
      ~EventHandler();

      bool matches(const ev::Event&) const;
      cub::Status handleEvent(const ev::Event&, EventHandlerExecuter&);

   private:
      DummyEventHandlerClass* thisPointer;
      DummyEventHandler handler;
      ev::EventId eventId;
   };

   int allocSlot() const;

private:
   enum
   {
      MAX_EVENT_HANDLER = 2
   };

   struct Handler
   {
      Handler();

      void* alloc(bool forever=false);
      bool matches(const ev::Event& event) const;
      bool isFree() const;
      void clear();
      void reset();

      cub::Placement<EventHandler> handler;

   private:
      bool forever;
      bool used;
   };

   Handler handlers[MAX_EVENT_HANDLER];
};

TSL_NS_END

#endif /* EVENTHANDLERREGISTRY_H_ */
