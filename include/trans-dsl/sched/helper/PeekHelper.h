/*
 * PeekHelper.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PEEKHELPER_H_
#define PEEKHELPER_H_

#include "trans-dsl/sched/action/SchedPeekAction.h"

namespace details
{
   template <EventId EVENT_ID>
   struct PEEK__ : SchedPeekAction
   {
      OVERRIDE(EventId getEventId() const)
      {
         return EVENT_ID;
      }
   };
}

////////////////////////////////////////////////////////////////////
#define __peek(...) \
       details::PEEK__< __VA_ARGS__ >

////////////////////////////////////////////////////////////////////

#endif /* PEEKHELPER_H_ */
