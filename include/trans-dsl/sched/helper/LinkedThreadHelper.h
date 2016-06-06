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

namespace details
{
   template <typename T_ACTION>
   struct LINKED_THREAD__ : LinkedActionThread
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

#endif /* LINKEDTHREADHELPER_H_ */
