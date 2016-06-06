/*
 * TransMutexSchedulerAdapter.cpp
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/trans/TransMutexSchedulerAdapter.h"
#include "base/utils/Assertions.h"

//////////////////////////////////////////////////////////////////////////////////
TransMutexSchedulerAdapter::TransMutexSchedulerAdapter()
   : scheduler(0)
{
}

//////////////////////////////////////////////////////////////////////////////////
Status TransMutexSchedulerAdapter::lock(TransMutexId mutex)
{
   return (scheduler != 0) ? scheduler->lock(mutex) : SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////
void TransMutexSchedulerAdapter::unlock(TransMutexId mutex)
{
   if(scheduler != 0)
   {
      scheduler->unlock(mutex);
   }
}

//////////////////////////////////////////////////////////////////////////////////
void TransMutexSchedulerAdapter::updateMutexScheduler(TransMutexScheduler& scheduler)
{
   this->scheduler = &scheduler;
}
