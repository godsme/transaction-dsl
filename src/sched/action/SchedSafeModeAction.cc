/*
 * SchedSafeModeAction.cc
 *
 * Created on: Jun 10, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/sched/action/SchedSafeModeAction.h"
#include "trans-dsl/utils/ActionStatus.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/sched/concept/TransactionMode.h"

TSL_NS_BEGIN

using namespace cub;

///////////////////////////////////////////////////////////////////////////////////
Status SchedSafeModeAction::final(TransactionContext& context, Status status)
{
   if(!ActionStatus(status).isWorking())
   {
      context.getTransactionMode().leaveSafeMode();
   }

   return status;
}

///////////////////////////////////////////////////////////////////////////////////
#define FINAL(method) final(context, ROLE(SchedAction).method)

///////////////////////////////////////////////////////////////////////////////////
Status SchedSafeModeAction::exec(TransactionContext& context)
{
   context.getTransactionMode().enterSafeMode();

   return FINAL(exec(context));
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSafeModeAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return FINAL(handleEvent(context, event));
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSafeModeAction::stop(TransactionContext& context, const Status cause)
{
   return FINAL(stop(context, cause));
}

///////////////////////////////////////////////////////////////////////////////////
void SchedSafeModeAction::kill(TransactionContext& context, const Status cause)
{
   ROLE(SchedAction).kill(context, cause);
   context.getTransactionMode().leaveSafeMode();
}

TSL_NS_END
