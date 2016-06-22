/*
 * RelativeTimer.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include <trans-dsl/utils/RelativeTimer.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <trans-dsl/sched/concept/TimerInfo.h>

#include <cub/base/Assertions.h>

TSL_NS_BEGIN

using namespace cub;

/////////////////////////////////////////////////////////////////
RelativeTimer::RelativeTimer(const TimerId timerId)
   : timerId(timerId)
   , started(false)
{
}

/////////////////////////////////////////////////////////////////
Status RelativeTimer::start(const TimerInfo& info)
{
   stop();

   U32 len = info.getTimerLen(timerId);
   CUB_ASSERT_TRUE(len > 0);

   CUB_ASSERT_SUCC_CALL(actualStartTimer(timerId, len));

   started = true;

   return TSL_SUCCESS;
}

/////////////////////////////////////////////////////////////////
void RelativeTimer::stop()
{
   if(!started) return;

   actualStopTimer(timerId);
}

/////////////////////////////////////////////////////////////////
bool RelativeTimer::matches(const ev::Event& event) const
{
   if(!started || !isTimerEvent(event)) return false;

   return actualMatches(event, timerId);
}

TSL_NS_END
