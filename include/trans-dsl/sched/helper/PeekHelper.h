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

#include <trans-dsl/sched/action/SchedPeekAction.h>

TSL_NS_BEGIN

namespace details
{
   template <ev::EventId EVENT_ID>
   struct PEEK__ : SchedPeekAction
   {
      OVERRIDE(ev::EventId getEventId() const)
      {
         return EVENT_ID;
      }
   };
}

TSL_NS_END

////////////////////////////////////////////////////////////////////
#define __peek(...) \
       tsl::details::PEEK__< __VA_ARGS__ >

////////////////////////////////////////////////////////////////////

#endif /* PEEKHELPER_H_ */
