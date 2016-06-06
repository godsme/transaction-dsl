/*
 * SchedForkAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "trans-dsl/ext/multi-thread/action/SchedForkAction.h"
#include "trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "base/dci/Unknown.h"
#include "base/utils/Assertions.h"
#include "trans-dsl/utils/ActionStatus.h"

Status SchedForkAction::exec(TransactionContext& context)
{
   MultiThreadContext* mt = unknown_cast<MultiThreadContext>(&context);
   DCM_ASSERT_VALID_PTR(mt);

   Status result = SUCCESS;
   DCM_ASSERT_SUCC_CALL(mt->startThread(getThreadId(), ROLE(ActionThread), result));

   if(ActionStatus(result).isFailed())
   {
      return result;
   }

   return SUCCESS;
}

Status SchedForkAction::handleEvent(TransactionContext&, const Event&)
{
   return UNKNOWN_EVENT;
}

Status SchedForkAction::stop(TransactionContext&, Status)
{
   return SUCCESS;
}

void   SchedForkAction::kill(TransactionContext&, Status)
{
}


