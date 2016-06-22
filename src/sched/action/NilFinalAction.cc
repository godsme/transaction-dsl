/*
 * NilFinalAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "trans-dsl/sched/action/NilFinalAction.h"
#include "trans-dsl/sched/concept/TransactionContext.h"

Status NilFinalAction::exec(TransactionContext&)
{
   return SUCCESS;
}

Status NilFinalAction::handleEvent(TransactionContext&, const Event&)
{
   return FATAL_BUG;
}

void NilFinalAction::kill(TransactionContext&, const Status)
{
}
