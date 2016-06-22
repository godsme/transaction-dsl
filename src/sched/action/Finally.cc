/*
 * Finally.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include "trans-dsl/sched/action/Finally.h"
#include "trans-dsl/sched/concept/SchedAction.h"

Status Finally::exec(TransactionContext& context)
{
   return ROLE(SchedAction).exec(context);
}

Status Finally::handleEvent(TransactionContext& context, const Event& event)
{
   return ROLE(SchedAction).handleEvent(context, event);
}

void Finally::kill(TransactionContext& context, Status cause)
{
   return ROLE(SchedAction).kill(context, cause);
}
