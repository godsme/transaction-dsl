/*
 * Transaction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include <trans-dsl/sched/concept/Transaction.h>
#include <trans-dsl/utils/ActionStatus.h>

TSL_NS_BEGIN

cub::Status Transaction::start(const ev::Event& event)
{
   ActionStatus status = start();
   if(!status.isWorking())
   {
      return status;
   }

   return handleEvent(event);
}

TSL_NS_END

