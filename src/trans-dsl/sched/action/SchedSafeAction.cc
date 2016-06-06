/*
 * SchedSafeAction.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/action/SchedSafeAction.h"
#include "trans-dsl/utils/ActionStatus.h"

SchedSafeAction::SchedSafeAction()
   : running(false)
{
}

Status SchedSafeAction::final(const Status status)
{
    running = ActionStatus(status).isWorking();

    return status;
}

Status SchedSafeAction::exec(TransactionContext& context)
{
   if(running) return CONTINUE;

   return final(ROLE(SchedAction).exec(context));
}

Status SchedSafeAction::handleEvent(TransactionContext& context, const Event& event)
{
   if(!running) return UNKNOWN_EVENT;

   return final(ROLE(SchedAction).handleEvent(context, event));
}

Status SchedSafeAction::stop(TransactionContext&, Status)
{
   return running ? CONTINUE : SUCCESS;
}

void SchedSafeAction::kill(TransactionContext& context, Status cause)
{
   if(running) ROLE(SchedAction).kill(context, cause);
}
