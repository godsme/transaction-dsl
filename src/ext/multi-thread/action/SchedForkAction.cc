/*
 * SchedForkAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include <trans-dsl/ext/multi-thread/action/SchedForkAction.h>
#include <trans-dsl/ext/multi-thread/concept/MultiThreadContext.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <cub/base/Assertions.h>
#include <cub/dci/Unknown.h>

TSL_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////////
cub::Status SchedForkAction::exec(TransactionContext& context)
{
   MultiThreadContext* mt = com::unknown_cast<MultiThreadContext>(&context);
   CUB_ASSERT_VALID_PTR(mt);

   cub::Status result = TSL_SUCCESS;
   CUB_ASSERT_SUCC_CALL(mt->startThread(getThreadId(), ROLE(ActionThread), result));

   if(ActionStatus(result).isFailed())
   {
      return result;
   }

   return TSL_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////
cub::Status SchedForkAction::handleEvent(TransactionContext&, const ev::Event&)
{
   return TSL_UNKNOWN_EVENT;
}

//////////////////////////////////////////////////////////////////////////////////
cub::Status SchedForkAction::stop(TransactionContext&, cub::Status)
{
   return TSL_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////
void   SchedForkAction::kill(TransactionContext&, cub::Status)
{
}

TSL_NS_END

