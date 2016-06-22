/*
 * TransMutexSchedulerAdapter.cpp
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/sched/trans/TransMutexSchedulerAdapter.h>
#include <trans-dsl/TslStatus.h>

TSL_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////////
TransMutexSchedulerAdapter::TransMutexSchedulerAdapter()
   : scheduler(0)
{
}

//////////////////////////////////////////////////////////////////////////////////
cub::Status TransMutexSchedulerAdapter::lock(TransMutexId mutex)
{
   return (scheduler != 0) ? scheduler->lock(mutex) : TSL_SUCCESS;
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

TSL_NS_END
