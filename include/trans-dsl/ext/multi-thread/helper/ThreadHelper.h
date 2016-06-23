/*
 * ThreadHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef THREADHELPER_H_
#define THREADHELPER_H_

#include "trans-dsl/sched/action/ActionThread.h"

TSL_NS_BEGIN

namespace details
{
   template<typename T_ACTION>
   struct THREAD__: ActionThread
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
};

TSL_NS_END

#endif /* THREADHELPER_H_ */
