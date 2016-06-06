/*
 * VoidHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef VOIDHELPER_H_
#define VOIDHELPER_H_

#include "trans-dsl/sched/action/SchedVoidAction.h"

namespace details
{
   template <typename T_ACTION>
   struct VOID__ : SchedVoidAction
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

////////////////////////////////////////////////////////////
#define __void(...) details::VOID__< __VA_ARGS__ >

////////////////////////////////////////////////////////////

#endif /* VOIDHELPER_H_ */
