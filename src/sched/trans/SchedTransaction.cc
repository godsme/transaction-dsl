/*
 * SchedTransaction.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 
#include <trans-dsl/sched/trans/SchedTransaction.h>
#include <trans-dsl/sched/concept/TransactionScheduler.h>
#include <cub/log/log.h>

TSL_NS_BEGIN

using namespace cub;

//////////////////////////////////////////////////////////////////////////////
Status SchedTransaction::start()
{
   return ROLE(TransactionScheduler).start(ROLE(ActionThread));
}

//////////////////////////////////////////////////////////////////////////////
Status SchedTransaction::handleEvent(const ev::Event& event)
{
    return ROLE(TransactionScheduler).handleEvent(event);
}

//////////////////////////////////////////////////////////////////////////////
Status SchedTransaction::stop(const StopCause& cause)
{
   return ROLE(TransactionScheduler).stop(cause);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::kill(const StopCause& cause)
{
   ROLE(TransactionScheduler).kill(cause);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::updateInstanceId(InstanceId iid)
{
   ROLE(TransactionScheduler).updateInstanceId(iid);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::updateTimerInfo(const TimerInfo& info)
{
   ROLE(TransactionScheduler).updateTimerInfo(info);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::updateTransactionListener(TransactionListener& listener)
{
   ROLE(TransactionScheduler).updateTransactionListener(listener);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::updateUserContext(com::Unknown* context)
{
   ROLE(TransactionScheduler).updateUserContext(context);
}

//////////////////////////////////////////////////////////////////////////////
void SchedTransaction::updateMutexScheduler(TransMutexScheduler& scheduler)
{
   ROLE(TransactionScheduler).updateMutexScheduler(scheduler);
}

TSL_NS_END
