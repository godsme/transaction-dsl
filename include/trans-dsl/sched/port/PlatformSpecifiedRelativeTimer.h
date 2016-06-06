/*
 * PlatformSpecifiedRelativeTimer.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PLATFORMSPECIFIEDRELATIVETIMER_H_
#define PLATFORMSPECIFIEDRELATIVETIMER_H_

#include "trans-dsl/utils/RelativeTimer.h"

struct PlatformSpecifiedRelativeTimer : RelativeTimer
{
   PlatformSpecifiedRelativeTimer(const TimerId timerId);

private:
   OVERRIDE(bool isTimerEvent(const Event&) const);
   OVERRIDE(Status actualStartTimer(const TimerId, WORD32 timerLen));
   OVERRIDE(void actualStopTimer(const TimerId));
   OVERRIDE(bool actualMatches(const Event&, const TimerId) const);
};

#endif /* PLATFORMSPECIFIEDRELATIVETIMER_H_ */
