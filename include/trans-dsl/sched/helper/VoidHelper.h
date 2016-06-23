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

#include <trans-dsl/sched/action/SchedVoidAction.h>

TSL_NS_BEGIN

namespace details
{
   template <typename T_ACTION>
   struct VOID__ : SchedVoidAction
   {
       IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

TSL_NS_END

////////////////////////////////////////////////////////////
#define __void(...) TSL_NS::details::VOID__< __VA_ARGS__ >

////////////////////////////////////////////////////////////

#endif /* VOIDHELPER_H_ */
