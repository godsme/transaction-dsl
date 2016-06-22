/*
 * PlatformSpecifiedRelativeTimer.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include <trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h>
#include <event/concept/Event.h>
#include <trans-dsl/TslStatus.h>

TSL_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////
PlatformSpecifiedRelativeTimer::PlatformSpecifiedRelativeTimer(
         const TimerId timerId)
   : RelativeTimer(timerId)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
   const ev::EventId TIMER_EVENT_START = 400;
   const ev::EventId TIMER_EVENT_END   = 430;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PlatformSpecifiedRelativeTimer::isTimerEvent(const ev::Event& event) const
{
   return event.getEventId() >= TIMER_EVENT_START && event.getEventId() < TIMER_EVENT_END;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
cub::Status PlatformSpecifiedRelativeTimer::actualStartTimer(const TimerId, cub::U32)
{
   return TSL_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlatformSpecifiedRelativeTimer::actualStopTimer(const TimerId)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PlatformSpecifiedRelativeTimer::actualMatches(const ev::Event& event, const TimerId timerId) const
{
   return timerId + TIMER_EVENT_START == event.getEventId();
}

TSL_NS_END
