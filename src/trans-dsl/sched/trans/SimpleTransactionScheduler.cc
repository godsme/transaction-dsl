/*
 * SimpleTransactionScheduler.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/trans/SimpleTransactionScheduler.h"
#include "trans-dsl/sched/action/ActionThread.h"

///////////////////////////////////////////////////////////////////////////////
SimpleTransactionScheduler::SimpleTransactionScheduler(InstanceId iid)
      : BaseTransactionScheduler(iid)
      , thread(0)
{
}

///////////////////////////////////////////////////////////////////////////////
SimpleTransactionScheduler::SimpleTransactionScheduler
      ( RuntimeContext& runtimeContext
      , InstanceId iid)
      : BaseTransactionScheduler(runtimeContext, iid)
      , thread(0)
{
}

///////////////////////////////////////////////////////////////////////////////
Status SimpleTransactionScheduler::start(ActionThread& thread)
{
   this->thread = &thread;
   return thread.exec(*this);
}

///////////////////////////////////////////////////////////////////////////////
Status SimpleTransactionScheduler::handleEvent(const Event& event)
{
   return thread->handleEvent(*this, event);
}

///////////////////////////////////////////////////////////////////////////////
Status SimpleTransactionScheduler::actualStop(const Status cause)
{
   return thread->stop(*this, cause);
}

///////////////////////////////////////////////////////////////////////////////
bool SimpleTransactionScheduler::isWorking() const
{
   return thread->isWorking();
}

///////////////////////////////////////////////////////////////////////////////
void SimpleTransactionScheduler::kill(const Status cause)
{
   thread->kill(*this, cause);
}
