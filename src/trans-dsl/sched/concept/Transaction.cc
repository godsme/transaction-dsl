/*
 * Transaction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/concept/Transaction.h"
#include "trans-dsl/utils/ActionStatus.h"

Status Transaction::start(const Event& event)
{
   ActionStatus status = start();
   if(!status.isWorking())
   {
      return status;
   }

   return handleEvent(event);
}


