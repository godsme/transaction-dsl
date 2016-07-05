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

#include <cub/base/Status.h>
#include <cub/dci/Role.h>
#include <cub/dci/Unknown.h>
#include <trans-dsl/sched/concept/InstanceId.h>

FWD_DECL_EV(Event)

TSL_NS_BEGIN

struct ActionThread;
struct TransactionListener;
struct TimerInfo;
struct TransMutexScheduler;
struct UserContext;

DEFINE_ROLE(TransactionScheduler)
{
   ABSTRACT(cub::Status start(ActionThread&));
   ABSTRACT(cub::Status handleEvent(const ev::Event&));
   ABSTRACT(cub::Status stop(const cub::Status));
   ABSTRACT(void   kill(const cub::Status));

   ABSTRACT(void updateInstanceId(InstanceId iid));
   ABSTRACT(void updateTimerInfo(const TimerInfo&));
   ABSTRACT(void updateTransactionListener(TransactionListener&));
   ABSTRACT(void updateUserContext(com::Unknown*));
   ABSTRACT(void updateMutexScheduler(TransMutexScheduler&));
};

TSL_NS_END

#endif /* TRANSACTIONSCHEDULER_H_ */
