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

#include <trans-dsl/sched/action/SchedWaitAction.h>

TSL_NS_BEGIN

namespace details
{
   template <ev::EventId EVENT_ID>
   struct WAIT__ : SchedWaitAction
   {
      OVERRIDE(ev::EventId getEventId() const)
      {
         return EVENT_ID;
      }
   };
}

TSL_NS_END


///////////////////////////////////////////////////////////
#define __wait(...) \
       TSL_NS::details::WAIT__< __VA_ARGS__ >

///////////////////////////////////////////////////////////

#endif /* WAITHELPER_H_ */
