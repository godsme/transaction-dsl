/*
 * ActionHelper.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONHELPER_H_
#define ACTIONHELPER_H_

#include <trans-dsl/sched/action/SchedActionAdapter.h>
#include <trans-dsl/action/SyncActionAdapter.h>

TSL_NS_BEGIN

namespace details
{
   template<typename T_ACTION>
   struct ACTION__: tsl::SchedActionAdapter
   {
       IMPL_ROLE_WITH_VAR(Action, T_ACTION);
   };

   template <typename T_ASYN_ACTION>
   struct ASYN__ : ACTION__<T_ASYN_ACTION>
   {
   };

   template<typename T_SYNC_ACTION>
   struct GenericSyncAtionAdpater: tsl::SyncActionAdapter
   {
   private:
       IMPL_ROLE_WITH_VAR(SyncAction, T_SYNC_ACTION);
   };

   template <typename T_SYNC_ACTION>
   struct SYNC__ : ACTION__<GenericSyncAtionAdpater<T_SYNC_ACTION> >
   {
   };
}

TSL_NS_END

////////////////////////////////////////////////////////////////////////
#define __asyn(action, ...) \
       TSL_NS::details::ASYN__< action __VA_ARGS__ >

#define __sync(action, ...) \
       TSL_NS::details::SYNC__< action __VA_ARGS__ >

////////////////////////////////////////////////////////////////////////
#define __ind(...)  __sync(__VA_ARGS__)
#define __call(...) __sync(__VA_ARGS__)
#define __req(...)  __asyn(__VA_ARGS__)
#define __rsp(...)  __sync(__VA_ARGS__)

#define __onto(actor)    < actor >
////////////////////////////////////////////////////////////////////////

#endif /* ACTIONHELPER_H_ */
