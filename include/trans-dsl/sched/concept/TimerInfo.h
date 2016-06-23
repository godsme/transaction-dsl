/*
 * TimerInfo.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TIMERINFO_H_
#define TIMERINFO_H_

#include <cub/base/BaseTypes.h>
#include <cub/dci/InterfaceDef.h>
#include <cub/dci/Role.h>
#include <trans-dsl/sched/concept/TimerId.h>

TSL_NS_BEGIN

UNKNOWN_INTERFACE(TimerInfo, 32302582)
{
   ABSTRACT(cub::U32 getTimerLen(const TimerId) const);
};

TSL_NS_END

#endif /* TIMINGINFO_H_ */
