/*
 * SchedPeekAction.cc
 *
 *  Created on: Apr 28, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/action/SchedPeekAction.h"
#include "event/concept/Event.h"

Status SchedPeekAction::exec(TransactionContext&)
{
   return CONTINUE;
}

Status SchedPeekAction::handleEvent(TransactionContext&, const Event& event)
{
   if(event.matches(getEventId()))
   {
      return SUCCESS;
   }

   return UNKNOWN_EVENT;
}

Status SchedPeekAction::stop(TransactionContext&, const Status cause)
{
   return cause;
}

void SchedPeekAction::kill(TransactionContext&, const Status)
{
}
