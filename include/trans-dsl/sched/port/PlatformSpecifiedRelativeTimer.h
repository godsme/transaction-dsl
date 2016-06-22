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

#include <trans-dsl/utils/RelativeTimer.h>

TSL_NS_BEGIN

struct PlatformSpecifiedRelativeTimer : RelativeTimer
{
   PlatformSpecifiedRelativeTimer(const TimerId timerId);

private:
   OVERRIDE(bool isTimerEvent(const ev::Event&) const);
   OVERRIDE(cub::Status actualStartTimer(const TimerId, cub::U32 timerLen));
   OVERRIDE(void actualStopTimer(const TimerId));
   OVERRIDE(bool actualMatches(const ev::Event&, const TimerId) const);
};

TSL_NS_END

#endif /* PLATFORMSPECIFIEDRELATIVETIMER_H_ */
