/*
 * SafeHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SAFEHELPER_H_
#define SAFEHELPER_H_

#include "trans-dsl/sched/action/SchedSafeAction.h"

TSL_NS_BEGIN

namespace details
{
   template <typename T_ACTION>
   struct SAFE__ : SchedSafeAction
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
};

TSL_NS_END

////////////////////////////////////////////////////////////////////
#define __safe(...) TSL_NS::details::SAFE__< __VA_ARGS__ >

#endif /* UNSTOPHELPER_H_ */
