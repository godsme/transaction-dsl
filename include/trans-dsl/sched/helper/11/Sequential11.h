/*
 * Sequential11.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SEQUENTIAL11_H_
#define SEQUENTIAL11_H_

#include "trans-dsl/sched/action/SchedSequentialAction.h"
#include "trans-dsl/sched/helper/LinkedHelper.h"
#include "trans-dsl/sched/helper/VoidHelper.h"

TSL_NS_BEGIN

namespace details
{
   template <typename... T_ACTIONS> struct GenericSequential;

   template <typename T_HEAD, typename... T_TAIL>
   struct GenericSequential<T_HEAD, T_TAIL...> : GenericSequential<T_TAIL...>
   {
   protected:
      void init()
      {
         GenericSequential<T_TAIL...>::pushBackAction(action);
         GenericSequential<T_TAIL...>::init();
      }
   private:
      details::LINKED__< T_HEAD > action;
   };

   template <>
   struct GenericSequential<> : tsl::SchedSequentialAction
   {
   protected:
      void init() {}
   };

   template <typename... T_ACTIONS>
   struct SEQUENTIAL__ : GenericSequential<T_ACTIONS...>
   {
      SEQUENTIAL__()
      {
         GenericSequential<T_ACTIONS...>::init();
      }
   };

   /////////////////////////////////////////////////////////
   template <typename... T_ACTIONS> struct VoidGenericSequential;

   template <typename T_HEAD, typename... T_TAIL>
   struct VoidGenericSequential<T_HEAD, T_TAIL...> : VoidGenericSequential<T_TAIL...>
   {
   protected:
      void init()
      {
         VoidGenericSequential<T_TAIL...>::pushBackAction(action);
         VoidGenericSequential<T_TAIL...>::init();
      }
   private:
      details::LINKED__< details::VOID__< T_HEAD > > action;
   };

   template <>
   struct VoidGenericSequential<> : tsl::SchedSequentialAction
   {
   protected:
      void init() {}
   };

   template <typename... T_ACTIONS>
   struct VOID_SEQUENTIAL__ : VoidGenericSequential<T_ACTIONS...>
   {
      VOID_SEQUENTIAL__()
      {
         VoidGenericSequential<T_ACTIONS...>::init();
      }
   };
}

TSL_NS_END

#endif /* SEQUENTIAL11_H_ */
