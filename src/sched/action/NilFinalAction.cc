/*
 * NilFinalAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include <trans-dsl/sched/action/NilFinalAction.h>
#include <trans-dsl/sched/concept/TransactionContext.h>

TSL_NS_BEGIN

cub::Status NilFinalAction::exec(TransactionContext&)
{
   return TSL_SUCCESS;
}

cub::Status NilFinalAction::handleEvent(TransactionContext&, const ev::Event&)
{
   return TSL_FATAL_BUG;
}

void NilFinalAction::kill(TransactionContext&, const cub::Status)
{
}

TSL_NS_END
