/*
 * SafeModeHelper.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SAFEMODEHELPER_H_
#define SAFEMODEHELPER_H_

#include "trans-dsl/sched/action/SchedSafeModeAction.h"

namespace details
{
   template <typename T_ACTION>
   struct SAFE_MODE__ : SchedSafeModeAction
   {
   private:
         IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

#define __safe_mode(...) details::SAFE_MODE__< __VA_ARGS__ >

#endif /* SAFEMODEHELPER_H_ */
