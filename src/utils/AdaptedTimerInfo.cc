/*
 * AdaptedTimerInfo.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include "trans-dsl/utils/AdaptedTimerInfo.h"

AdaptedTimerInfo::AdaptedTimerInfo()
   : timerInfo(0)
{
}

WORD32 AdaptedTimerInfo::getTimerLen(const TimerId id) const
{
   return timerInfo == 0 ? 0 : timerInfo->getTimerLen(id);
}

void AdaptedTimerInfo::setTimerInfo(const TimerInfo* timerInfo)
{
   this->timerInfo = timerInfo;
}
