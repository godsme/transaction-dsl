/*
 * WaitHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef WAITHELPER_H_
#define WAITHELPER_H_

#include "trans-dsl/sched/action/SchedWaitAction.h"

namespace details
{
   template <EventId EVENT_ID>
   struct WAIT__ : SchedWaitAction
   {
      OVERRIDE(EventId getEventId() const)
      {
         return EVENT_ID;
      }
   };
}

///////////////////////////////////////////////////////////
#define __wait(...) \
       details::WAIT__< __VA_ARGS__ >

///////////////////////////////////////////////////////////

#endif /* WAITHELPER_H_ */
