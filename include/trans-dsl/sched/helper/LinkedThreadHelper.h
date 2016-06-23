/*
 * LinkedThreadHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDTHREADHELPER_H_
#define LINKEDTHREADHELPER_H_

#include "trans-dsl/sched/action/LinkedActionThread.h"

TSL_NS_BEGIN

namespace details
{
   template <typename T_ACTION>
   struct LINKED_THREAD__ : tsl::LinkedActionThread
   {
       typedef tsl::SchedAction SchedAction;

   private:
       IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

TSL_NS_END

#endif /* LINKEDTHREADHELPER_H_ */
