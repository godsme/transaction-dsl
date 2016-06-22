/*
 * SchedActionAdapter.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include <trans-dsl/sched/action/SchedActionAdapter.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/action/Action.h>

TSL_NS_BEGIN

////////////////////////////////////////////////////////////////
cub::Status SchedActionAdapter::exec(TransactionContext& context)
{
   return ROLE(Action).exec(context.ROLE(TransactionInfo));
}

////////////////////////////////////////////////////////////////
cub::Status SchedActionAdapter::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return ROLE(Action).handleEvent(context.ROLE(TransactionInfo), event);
}

////////////////////////////////////////////////////////////////
cub::Status SchedActionAdapter::stop(TransactionContext& context, const cub::Status cause)
{
   ROLE(Action).kill(context.ROLE(TransactionInfo), cause);

   return cause;
}

////////////////////////////////////////////////////////////////
void SchedActionAdapter::kill(TransactionContext& context, const cub::Status cause)
{
   ROLE(Action).kill(context.ROLE(TransactionInfo), cause);
}

TSL_NS_END

