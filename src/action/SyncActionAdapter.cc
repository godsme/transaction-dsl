/*
 * SyncActionAdapter.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include <trans-dsl/action/SyncActionAdapter.h>
#include <trans-dsl/utils/ActionStatus.h>
#include <trans-dsl/TslStatus.h>

TSL_NS_BEGIN

///////////////////////////////////////////////////////
cub::Status SyncActionAdapter::exec(const TransactionInfo& trans)
{
   ActionStatus status = ROLE(SyncAction).exec(trans);
   if(status.isWorking())
   {
      return TSL_FATAL_BUG;
   }

   return status;
}

//////////////////////////////////////////////////////////////////////
cub::Status SyncActionAdapter::handleEvent(const TransactionInfo&, const ev::Event&)
{
   return TSL_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////
void SyncActionAdapter::kill(const TransactionInfo&, const cub::Status)
{
}

TSL_NS_END

