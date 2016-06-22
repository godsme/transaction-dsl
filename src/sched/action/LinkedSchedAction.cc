/*
 * LinkedSchedAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include <trans-dsl/sched/action/LinkedSchedAction.h>

TSL_NS_BEGIN

/////////////////////////////////////////////////////////////////////////////////////////
cub::Status LinkedSchedAction::exec(TransactionContext& context)
{
   return ROLE(SchedAction).exec(context);
}

/////////////////////////////////////////////////////////////////////////////////////////
cub::Status LinkedSchedAction::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return ROLE(SchedAction).handleEvent(context, event);
}

/////////////////////////////////////////////////////////////////////////////////////////
cub::Status LinkedSchedAction::stop(TransactionContext& context, const cub::Status cause)
{
   return ROLE(SchedAction).stop(context, cause);
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedSchedAction::kill(TransactionContext& context, const cub::Status cause)
{
   ROLE(SchedAction).kill(context, cause);
}

TSL_NS_END

