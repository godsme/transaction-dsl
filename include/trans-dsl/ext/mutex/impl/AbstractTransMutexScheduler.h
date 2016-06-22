/*
 * AbstractTransMutexScheduler.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ABSTRACTTRANSMUTEXSCHEDULER_H_
#define ABSTRACTTRANSMUTEXSCHEDULER_H_

#include <trans-dsl/ext/mutex/concept/TransMutexScheduler.h>

TSL_NS_BEGIN

struct TransMutexAvailNotifier;

struct AbstractTransMutexScheduler : TransMutexScheduler
{
   AbstractTransMutexScheduler();

   OVERRIDE(cub::Status lock(TransMutexId));
   OVERRIDE(void unlock(TransMutexId));

private:
   cub::U8 lockBitmap;

private:
   USE_ROLE(TransMutexAvailNotifier);
};

TSL_NS_END

#endif /* ABSTRACTTRANSMUTEXSCHEDULER_H_ */
