/*
 * RuntimeContextAutoSwitch.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/sched/concept/RuntimeContextInfo.h"
#include "base/dci/Unknown.h"

RuntimeContextAutoSwitch::RuntimeContextAutoSwitch
   ( RuntimeContext& newRuntimeContext
   , RuntimeContext*& parentKeeper
   , TransactionContext& context)
   : parentKeeper(parentKeeper)
   , contextInfo(unknown_cast<RuntimeContextInfo>(&context))
{
   if(contextInfo == 0)
   {
      parentKeeper = 0;
   }
   else
   {
      parentKeeper = contextInfo->getRuntimeContext();
      contextInfo->setRuntimeContext(newRuntimeContext);
   }
}

RuntimeContextAutoSwitch::~RuntimeContextAutoSwitch()
{
   if(contextInfo != 0)
   {
      contextInfo->setRuntimeContext(*parentKeeper);
   }
}
