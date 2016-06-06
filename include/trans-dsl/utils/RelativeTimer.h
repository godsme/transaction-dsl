/*
 * RelativeTimer.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RELATIVETIMER_H_
#define RELATIVETIMER_H_

#include "trans-dsl/sched/concept/TimerId.h"
#include <base/Status.h>
#include <base/Keywords.h>

struct Event;
struct TimerInfo;

struct RelativeTimer
{
   RelativeTimer(const TimerId timerId);

   Status start(const TimerInfo&);
   void stop();

   bool matches(const Event& event) const;

   virtual ~RelativeTimer() {}

private:
   const TimerId timerId;
   bool started;

private:
   ABSTRACT(bool isTimerEvent(const Event&) const);
   ABSTRACT(Status actualStartTimer(const TimerId, WORD32 timerLen));
   ABSTRACT(void actualStopTimer(const TimerId));
   ABSTRACT(bool actualMatches(const Event&, const TimerId) const);
};

#endif /* RELATIVETIMER_H_ */
