/*
 * LinkedHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDHELPER_H_
#define LINKEDHELPER_H_

#include "trans-dsl/sched/action/LinkedSchedAction.h"

namespace details
{
   template <typename T_ACTION>
   struct LINKED__ : LinkedSchedAction
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

#endif /* LINKEDHELPER_H_ */
