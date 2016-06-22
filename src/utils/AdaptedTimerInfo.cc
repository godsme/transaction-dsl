/*
 * AdaptedTimerInfo.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include <trans-dsl/utils/AdaptedTimerInfo.h>

TSL_NS_BEGIN

////////////////////////////////////////////////////////////////
AdaptedTimerInfo::AdaptedTimerInfo()
   : timerInfo(0)
{
}

////////////////////////////////////////////////////////////////
cub::U32 AdaptedTimerInfo::getTimerLen(const TimerId id) const
{
   return timerInfo == 0 ? 0 : timerInfo->getTimerLen(id);
}

////////////////////////////////////////////////////////////////
void AdaptedTimerInfo::setTimerInfo(const TimerInfo* timerInfo)
{
   this->timerInfo = timerInfo;
}

TSL_NS_END
