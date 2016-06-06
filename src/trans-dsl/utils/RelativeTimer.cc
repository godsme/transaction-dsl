/*
 * RelativeTimer.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include "trans-dsl/utils/RelativeTimer.h"
#include "trans-dsl/utils/ActionStatus.h"
#include "trans-dsl/sched/concept/TimerInfo.h"
#include "base/utils/Assertions.h"

RelativeTimer::RelativeTimer(const TimerId timerId)
   : timerId(timerId)
   , started(false)
{
}

Status RelativeTimer::start(const TimerInfo& info)
{
   stop();

   WORD32 len = info.getTimerLen(timerId);
   DCM_ASSERT_TRUE(len > 0);

   DCM_ASSERT_SUCC_CALL(actualStartTimer(timerId, len));

   started = true;

   return SUCCESS;
}

void RelativeTimer::stop()
{
   if(!started) return;

   actualStopTimer(timerId);
}

bool RelativeTimer::matches(const Event& event) const
{
   if(!started || !isTimerEvent(event)) return false;

   return actualMatches(event, timerId);
}
