/*
 * SchedActionAdapter.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include "trans-dsl/sched/action/SchedActionAdapter.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/action/Action.h"

////////////////////////////////////////////////////////////////
Status SchedActionAdapter::exec(TransactionContext& context)
{
   return ROLE(Action).exec(context.ROLE(TransactionInfo));
}

////////////////////////////////////////////////////////////////
Status SchedActionAdapter::handleEvent(TransactionContext& context, const Event& event)
{
   return ROLE(Action).handleEvent(context.ROLE(TransactionInfo), event);
}

////////////////////////////////////////////////////////////////
Status SchedActionAdapter::stop(TransactionContext& context, const Status cause)
{
   ROLE(Action).kill(context.ROLE(TransactionInfo), cause);

   return cause;
}

////////////////////////////////////////////////////////////////
void SchedActionAdapter::kill(TransactionContext& context, const Status cause)
{
   ROLE(Action).kill(context.ROLE(TransactionInfo), cause);
}
