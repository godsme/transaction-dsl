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

#include <base/dci/Role.h>
#include <trans-dsl/ext/mutex/concept/TransMutextId.h>

DEFINE_ROLE(TransMutexAvailNotifier)
{
   ABSTRACT(void notifyMutexAvail(TransMutexId));
};

#endif /* TRANSMUTEXAVAILNOTIFIER_H_ */
