/*
 * PlatformSpecifiedRelativeTimer.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h"
#include "event/concept/Event.h"

PlatformSpecifiedRelativeTimer::PlatformSpecifiedRelativeTimer(
         const TimerId timerId)
   : RelativeTimer(timerId)
{
}

namespace
{
   const EventId TIMER_EVENT_START = 400;
   const EventId TIMER_EVENT_END   = 430;
}

bool PlatformSpecifiedRelativeTimer::isTimerEvent(const Event& event) const
{
   return event.getEventId() >= TIMER_EVENT_START && event.getEventId() < TIMER_EVENT_END;
}

Status PlatformSpecifiedRelativeTimer::actualStartTimer(const TimerId, WORD32)
{
   return SUCCESS;
}

void PlatformSpecifiedRelativeTimer::actualStopTimer(const TimerId)
{
}

bool PlatformSpecifiedRelativeTimer::actualMatches(const Event& event, const TimerId timerId) const
{
   return timerId + TIMER_EVENT_START == event.getEventId();
}
