/*
 * SleepHelper.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SLEEPHELPER_H_
#define SLEEPHELPER_H_

#include <trans-dsl/sched/action/SchedSleepAction.h>
#include <trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h>

TSL_NS_BEGIN

namespace details
{
   template<TimerId TIMER_ID>
   struct SLEEP__: SchedSleepAction
   {
      SLEEP__() : timer(TIMER_ID)
      {
      }

   private:
      mutable PlatformSpecifiedRelativeTimer timer;
      ROLE_PROTO_TYPE(RelativeTimer)
      {
         return timer;
      }
   };
}

TSL_NS_END

///////////////////////////////////////////////////////////////////
#define __sleep(tid) \
       tsl::details::SLEEP__<tid>

///////////////////////////////////////////////////////////////////

#endif /* SLEEPHELPER_H_ */
