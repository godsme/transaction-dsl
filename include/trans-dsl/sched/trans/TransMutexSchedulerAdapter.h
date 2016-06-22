/*
 * TransMutexSchedulerAdapter.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSMUTEXSCHEDULERADAPTER_H_
#define TRANSMUTEXSCHEDULERADAPTER_H_

#include <trans-dsl/ext/mutex/concept/TransMutexScheduler.h>

TSL_NS_BEGIN

struct TransMutexSchedulerAdapter : TransMutexScheduler
{
   TransMutexSchedulerAdapter();

   OVERRIDE(cub::Status lock(TransMutexId));
   OVERRIDE(void unlock(TransMutexId));

   void updateMutexScheduler(TransMutexScheduler&);

private:
   TransMutexScheduler* scheduler;
};

TSL_NS_END

#endif /* TRANSMUTEXSCHEDULERADAPTER_H_ */
