/*
 * Finally.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include <trans-dsl/sched/action/Finally.h>
#include <trans-dsl/sched/concept/SchedAction.h>

TSL_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
cub::Status Finally::exec(TransactionContext& context)
{
   return ROLE(SchedAction).exec(context);
}

//////////////////////////////////////////////////////////////////////////
cub::Status Finally::handleEvent(TransactionContext& context, const ev::Event& event)
{
   return ROLE(SchedAction).handleEvent(context, event);
}

//////////////////////////////////////////////////////////////////////////
void Finally::kill(TransactionContext& context, cub::Status cause)
{
   return ROLE(SchedAction).kill(context, cause);
}

TSL_NS_END

