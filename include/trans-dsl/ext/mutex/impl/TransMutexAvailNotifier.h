/*
 * TransMutexAvailNotifier.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSMUTEXAVAILNOTIFIER_H_
#define TRANSMUTEXAVAILNOTIFIER_H_

#include <cub/dci/Role.h>
#include <trans-dsl/ext/mutex/concept/TransMutextId.h>

TSL_NS_BEGIN

DEFINE_ROLE(TransMutexAvailNotifier)
{
   ABSTRACT(void notifyMutexAvail(TransMutexId));
};

TSL_NS_END

#endif /* TRANSMUTEXAVAILNOTIFIER_H_ */
