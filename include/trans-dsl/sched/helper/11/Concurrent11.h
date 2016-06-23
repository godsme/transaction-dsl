/*
 * Concurrent11.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef CONCURRENT11_H_
#define CONCURRENT11_H_

#include "trans-dsl/sched/action/SchedConcurrentAction.h"
#include "trans-dsl/sched/helper/LinkedThreadHelper.h"
#include "trans-dsl/sched/helper/VoidHelper.h"

TSL_NS_BEGIN

namespace details
{
   template <typename... T_ACTIONS> struct GenericConcurrent;

   template <typename T_HEAD, typename... T_TAIL>
   struct GenericConcurrent<T_HEAD, T_TAIL...> : GenericConcurrent<T_TAIL...>
   {
   protected:
      void init()
      {
         GenericConcurrent<T_TAIL...>::addThread(action);
         GenericConcurrent<T_TAIL...>::init();
      }
   private:
      details::LINKED_THREAD__< T_HEAD > action;
   };

   template <>
   struct GenericConcurrent<> : tsl::SchedConcurrentAction
   {
   protected:
      void init()
      {
      }
   };

   template <typename... T_ACTIONS>
   struct CONCURRENT__ : GenericConcurrent<T_ACTIONS...>
   {
      CONCURRENT__()
      {
         GenericConcurrent<T_ACTIONS...>::init();
      }
   };

   ///////////////////////////////////////////////////////////////////
   template <typename... T_ACTIONS> struct VoidGenericConcurrent;

   template <typename T_HEAD, typename... T_TAIL>
   struct VoidGenericConcurrent<T_HEAD, T_TAIL...> : VoidGenericConcurrent<T_TAIL...>
   {
   protected:
      void init()
      {
         VoidGenericConcurrent<T_TAIL...>::addThread(action);
         VoidGenericConcurrent<T_TAIL...>::init();
      }
   private:
      details::LINKED_THREAD__< details::VOID__< T_HEAD > > action;
   };

   template <>
   struct VoidGenericConcurrent<> : tsl::SchedConcurrentAction
   {
   protected:
      void init() {}
   };

   template <typename... T_ACTIONS>
   struct VOID_CONCURRENT__ : VoidGenericConcurrent<T_ACTIONS...>
   {
      VOID_CONCURRENT__()
      {
         VoidGenericConcurrent<T_ACTIONS...>::init();
      }
   };
}

TSL_NS_END

#endif /* CONCURRENT11_H_ */
