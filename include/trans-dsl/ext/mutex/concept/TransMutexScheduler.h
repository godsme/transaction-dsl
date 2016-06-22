/*
 * TransMutexScheduler.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSMUTEXSCHEDULER_H_
#define TRANSMUTEXSCHEDULER_H_

#include <cub/base/Status.h>
#include <cub/dci/Role.h>
#include <trans-dsl/ext/mutex/concept/TransMutextId.h>

TSL_NS_BEGIN

DEFINE_ROLE(TransMutexScheduler)
{
   ABSTRACT(cub::Status lock(TransMutexId));
   ABSTRACT(void unlock(TransMutexId));
};

TSL_NS_END

#endif /* TRANSMUTEXSCHEDULER_H_ */
