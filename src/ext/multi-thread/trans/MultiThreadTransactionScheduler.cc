/*
 * MultiThreadTransactionScheduler.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include <trans-dsl/ext/multi-thread/trans/MultiThreadTransactionScheduler.h>

TSL_NS_BEGIN

MultiThreadTransactionScheduler::MultiThreadTransactionScheduler(const InstanceId iid)
      : BaseTransactionScheduler((SimpleRuntimeContext&)*this, iid)
{
}

//////////////////////////////////////////////////////////////////////////////
cub::Status MultiThreadTransactionScheduler::start(ActionThread& thread)
{
   return MultiThreadScheduler::startMainThread(thread);
}

//////////////////////////////////////////////////////////////////////////////
cub::Status MultiThreadTransactionScheduler::handleEvent(const ev::Event& event)
{
   return MultiThreadScheduler::handleEvent(event);
}

//////////////////////////////////////////////////////////////////////////////
void MultiThreadTransactionScheduler::kill(const cub::Status cause)
{
   return MultiThreadScheduler::kill(cause);
}

//////////////////////////////////////////////////////////////////////////////
cub::Status MultiThreadTransactionScheduler::actualStop(const cub::Status cause)
{
   return MultiThreadScheduler::stop(cause);
}

//////////////////////////////////////////////////////////////////////////////
bool MultiThreadTransactionScheduler::isWorking() const
{
   return MultiThreadScheduler::isWorking();
}

TSL_NS_END
