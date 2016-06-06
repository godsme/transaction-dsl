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

#include <base/dci/Role.h>
#include <base/Status.h>
#include <base/utils/Placement.h>
#include <event/concept/EventId.h>

struct DummyEventHandlerClass
{
   void dummy()
   {
   }
};

typedef void (DummyEventHandlerClass::*DummyEventHandler)();

///////////////////////////////////////////////////////////////
struct Event;

DEFINE_ROLE(EventHandlerExecuter)
{
   ABSTRACT(Status exec(const Event&, DummyEventHandlerClass*, DummyEventHandler));
};

///////////////////////////////////////////////////////////////
struct EventHandlerRegistry
{
   template<typename T, typename HANDLER>
   Status addHandler(const EventId eventId, T* thisPointer, HANDLER handler, bool forever = false)
   {
      return doAddHandler
               ( eventId
               , (DummyEventHandlerClass*) thisPointer
               , (DummyEventHandler) handler
               , forever);
   }

   Status addUntouchedEvent(const EventId eventId);

   Status handleEvent(const Event&, EventHandlerExecuter&);

   void reset();

private:
   Status doAddHandler(const EventId, DummyEventHandlerClass*,
            DummyEventHandler, bool forever);

   void clear();
private:

   struct EventHandler
   {
      EventHandler(const EventId, DummyEventHandlerClass*, DummyEventHandler);
      EventHandler(const EventId);
      EventHandler(const EventHandler& rhs);
      ~EventHandler();

      bool matches(const Event&) const;
      Status handleEvent(const Event&, EventHandlerExecuter&);

   private:
      DummyEventHandlerClass* thisPointer;
      DummyEventHandler handler;
      EventId eventId;
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
      bool matches(const Event& event) const;
      bool isFree() const;
      void clear();
      void reset();

      Placement<EventHandler> handler;

   private:
      bool forever;
      bool used;
   };

   Handler handlers[MAX_EVENT_HANDLER];
};

#endif /* EVENTHANDLERREGISTRY_H_ */
