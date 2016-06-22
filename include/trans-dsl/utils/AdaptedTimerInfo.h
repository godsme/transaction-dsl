/*
 * AdaptedTimerInfo.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ADAPTEDTIMERINFO_H_
#define ADAPTEDTIMERINFO_H_

#include <trans-dsl/sched/concept/TimerInfo.h>

TSL_NS_BEGIN

struct AdaptedTimerInfo : TimerInfo
{
   AdaptedTimerInfo();

   OVERRIDE(cub::U32 getTimerLen(const TimerId) const);

   void setTimerInfo(const TimerInfo* timerInfo);

private:
   const TimerInfo* timerInfo;
};

TSL_NS_END

#endif /* ADAPTEDTIMERINFO_H_ */
