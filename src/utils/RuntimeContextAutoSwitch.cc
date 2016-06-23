/*
 * RuntimeContextAutoSwitch.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include <cub/dci/Unknown.h>
#include <trans-dsl/utils/RuntimeContextAutoSwitch.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/sched/concept/RuntimeContextInfo.h>

TSL_NS_BEGIN

//////////////////////////////////////////////////////////////
RuntimeContextAutoSwitch::RuntimeContextAutoSwitch
   ( RuntimeContext& newRuntimeContext
   , RuntimeContext*& parentKeeper
   , TransactionContext& context)
   : parentKeeper(parentKeeper)
   , contextInfo(com::unknown_cast<RuntimeContextInfo>(&context))
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

//////////////////////////////////////////////////////////////
RuntimeContextAutoSwitch::~RuntimeContextAutoSwitch()
{
   if(contextInfo != 0)
   {
      contextInfo->setRuntimeContext(*parentKeeper);
   }
}

TSL_NS_END

