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

#include "trans-dsl/ext/mutex/concept/TransMutexScheduler.h"
#include <base/dci/Role.h>

struct TransMutexAvailNotifier;

struct AbstractTransMutexScheduler : TransMutexScheduler
{
   AbstractTransMutexScheduler();

   OVERRIDE(Status lock(TransMutexId));
   OVERRIDE(void unlock(TransMutexId));

private:
   BYTE lockBitmap;

private:
   USE_ROLE(TransMutexAvailNotifier);
};

#endif /* ABSTRACTTRANSMUTEXSCHEDULER_H_ */
