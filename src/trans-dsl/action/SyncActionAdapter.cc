/*
 * SyncActionAdapter.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include "trans-dsl/action/SyncActionAdapter.h"
#include "trans-dsl/utils/ActionStatus.h"

///////////////////////////////////////////////////////
Status SyncActionAdapter::exec(const TransactionInfo& trans)
{
   ActionStatus status = ROLE(SyncAction).exec(trans);
   if(status.isWorking())
   {
      return FATAL_BUG;
   }

   return status;
}

//////////////////////////////////////////////////////////////////////
Status SyncActionAdapter::handleEvent(const TransactionInfo&, const Event&)
{
   return UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////
void SyncActionAdapter::kill(const TransactionInfo&, const Status)
{
}
