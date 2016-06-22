/*
 * SimpleTransactionInfo.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/trans/SimpleTransactionInfo.h"
#include "trans-dsl/sched/concept/RuntimeContext.h"
#include "trans-dsl/sched/concept/RuntimeContextInfo.h"
#include "trans-dsl/utils/ActionStatus.h"

/////////////////////////////////////////////////////////////////
SimpleTransactionInfo::SimpleTransactionInfo(InstanceId iid)
  : iid(iid)
  , userContext(0)
{
}

/////////////////////////////////////////////////////////////////
InstanceId SimpleTransactionInfo::getInstanceId() const
{
   return iid;
}

void SimpleTransactionInfo::updateInstanceId(InstanceId iid)
{
   this->iid = iid;
}

/////////////////////////////////////////////////////////////////
Status SimpleTransactionInfo::getStatus() const
{
   RuntimeContext* context = ROLE(RuntimeContextInfo).getRuntimeContext();
   if(context == 0)
   {
      return SUCCESS;
   }

   if(ActionStatus(context->getStatus()).isFailed())
   {
      return context->getStatus();
   }

   return SUCCESS;
}

/////////////////////////////////////////////////////////////////
Unknown* SimpleTransactionInfo::getUserContext() const
{
   return userContext;
}

/////////////////////////////////////////////////////////////////
void SimpleTransactionInfo::updateUserContext(Unknown* userContext)
{
   this->userContext = userContext;
}
