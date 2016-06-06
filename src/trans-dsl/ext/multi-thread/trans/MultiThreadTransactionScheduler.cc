/*
 * MultiThreadTransactionScheduler.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/ext/multi-thread/trans/MultiThreadTransactionScheduler.h"

MultiThreadTransactionScheduler::MultiThreadTransactionScheduler(const InstanceId iid)
      : BaseTransactionScheduler((SimpleRuntimeContext&)*this, iid)
{
}

Status MultiThreadTransactionScheduler::start(ActionThread& thread)
{
   return MultiThreadScheduler::startMainThread(thread);
}

Status MultiThreadTransactionScheduler::handleEvent(const Event& event)
{
   return MultiThreadScheduler::handleEvent(event);
}

void MultiThreadTransactionScheduler::kill(const Status cause)
{
   return MultiThreadScheduler::kill(cause);
}

Status MultiThreadTransactionScheduler::actualStop(const Status cause)
{
   return MultiThreadScheduler::stop(cause);
}

bool MultiThreadTransactionScheduler::isWorking() const
{
   return MultiThreadScheduler::isWorking();
}
