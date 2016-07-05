/*
 * SchedTransaction.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDTRANSACTION_H_
#define SCHEDTRANSACTION_H_

#include <cub/dci/Unknown.h>
#include <trans-dsl/sched/concept/Transaction.h>
#include <trans-dsl/sched/concept/InstanceId.h>

TSL_NS_BEGIN

struct TimerInfo;
struct TransactionListener;
struct TransMutexScheduler;
struct UserContext;
struct TransactionScheduler;
struct ActionThread;

struct SchedTransaction : Transaction
{
   OVERRIDE(cub::Status start());
   OVERRIDE(cub::Status handleEvent(const ev::Event&));
   OVERRIDE(cub::Status stop(const StopCause& cause = StopCause()));
   OVERRIDE(void   kill(const StopCause& cause = StopCause()));

   void updateInstanceId(InstanceId iid);
   void updateTimerInfo(const TimerInfo&);
   void updateTransactionListener(TransactionListener&);
   void updateUserContext(com::Unknown*);
   void updateMutexScheduler(TransMutexScheduler&);

private:
   USE_ROLE(TransactionScheduler);
   USE_ROLE(ActionThread);
};

TSL_NS_END

#endif /* SCHEDTRANSACTION_H_ */
