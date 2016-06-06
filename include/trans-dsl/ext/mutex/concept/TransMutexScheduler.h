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

#include <trans-dsl/ext/mutex/concept/TransMutextId.h>
#include <base/dci/InterfaceDef.h>
#include <base/Status.h>

DEF_INTERFACE(TransMutexScheduler, 0x08060921)
{
   ABSTRACT(Status lock(TransMutexId));
   ABSTRACT(void unlock(TransMutexId));
};

#endif /* TRANSMUTEXSCHEDULER_H_ */
