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

#include "trans-dsl/sched/action/SchedSleepAction.h"
#include "trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h"

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

///////////////////////////////////////////////////////////////////
#define __sleep(tid) \
       details::SLEEP__<tid>

///////////////////////////////////////////////////////////////////

#endif /* SLEEPHELPER_H_ */
