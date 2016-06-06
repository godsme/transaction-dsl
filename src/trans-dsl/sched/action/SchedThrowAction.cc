/*
 * SchedThrowAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/action/SchedThrowAction.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/sched/concept/TransactionInfo.h"

Status SchedThrowAction::exec(TransactionContext& context)
{
   return getStatus() == RESERVED_FAILURE ? context.getTransactionInfo().getStatus() : getStatus();
}

////////////////////////////////////////////////////////////////////////
Status SchedThrowAction::handleEvent(TransactionContext&, const Event&)
{
   return FATAL_BUG;
}

////////////////////////////////////////////////////////////////////////
Status SchedThrowAction::stop(TransactionContext&, const Status)
{
   return FATAL_BUG;
}

////////////////////////////////////////////////////////////////////////
void SchedThrowAction::kill(TransactionContext&, const Status)
{
}
