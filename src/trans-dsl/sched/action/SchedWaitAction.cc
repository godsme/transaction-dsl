/*
 * SchedWaitAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/action/SchedWaitAction.h"
#include "event/concept/Event.h"

Status SchedWaitAction::exec(TransactionContext&)
{
   return CONTINUE;
}

Status SchedWaitAction::handleEvent(TransactionContext&, const Event& event)
{
   if(event.matches(getEventId()))
   {
      event.consume();
      return SUCCESS;
   }

   return UNKNOWN_EVENT;
}

Status SchedWaitAction::stop(TransactionContext&, const Status cause)
{
   return cause;
}

void SchedWaitAction::kill(TransactionContext&, const Status)
{
}
