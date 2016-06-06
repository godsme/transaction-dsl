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

#include <base/dci/InterfaceDef.h>
#include <base/IntTypes.h>
#include "trans-dsl/sched/concept/TimerId.h"

DEF_INTERFACE(TimerInfo, 1304241634)
{
   ABSTRACT(WORD32 getTimerLen(const TimerId) const);
};

#endif /* TIMINGINFO_H_ */
