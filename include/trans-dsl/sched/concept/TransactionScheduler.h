/*
 * TransactionScheduler.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONSCHEDULER_H_
#define TRANSACTIONSCHEDULER_H_

#include <base/dci/Role.h>
#include <base/Status.h>

struct ActionThread;
struct Event;
struct TransactionListener;
struct TimerInfo;
struct Unknown;
struct TransMutexScheduler;

DEFINE_ROLE(TransactionScheduler)
{
   ABSTRACT(Status start(ActionThread&));
   ABSTRACT(Status handleEvent(const Event&));
   ABSTRACT(Status stop(const Status));
   ABSTRACT(void   kill(const Status));

   ABSTRACT(void updateInstanceId(InstanceId iid));
   ABSTRACT(void updateTimerInfo(const TimerInfo&));
   ABSTRACT(void updateTransactionListener(TransactionListener&));
   ABSTRACT(void updateUserContext(Unknown*));
   ABSTRACT(void updateMutexScheduler(TransMutexScheduler&));
};

#endif /* TRANSACTIONSCHEDULER_H_ */
