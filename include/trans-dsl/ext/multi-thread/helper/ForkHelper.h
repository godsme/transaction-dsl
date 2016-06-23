/*
 * ForkHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FORKHELPER_H_
#define FORKHELPER_H_

#include "trans-dsl/ext/multi-thread/action/SchedForkAction.h"
#include "trans-dsl/ext/multi-thread/helper/ThreadHelper.h"

TSL_NS_BEGIN

namespace details
{
   template<ActionThreadId THREAD_ID, typename T_ACTION>
   struct FORK__: SchedForkAction
   {
   private:
      OVERRIDE(cub::U8 getThreadId() const)
      {
         return THREAD_ID;
      }

      typedef THREAD__<T_ACTION> Thread;

      IMPL_ROLE_WITH_VAR(ActionThread, Thread);
   };
}

TSL_NS_END

/////////////////////////////////////////////////////////
#define __fork(...) details::FORK__< __VA_ARGS__ >
/////////////////////////////////////////////////////////

#endif /* FORKHELPER_H_ */
