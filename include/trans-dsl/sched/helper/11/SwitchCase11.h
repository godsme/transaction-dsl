/*
 * SwitchCase11.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SWITCHCASE11_H_
#define SWITCHCASE11_H_

#include "trans-dsl/sched/action/SchedSwitchCaseAction.h"

namespace details
{
   template <typename... T_ACTION_PATHS> struct MultiPathCollection;

   template <typename T_HEAD, typename... T_TAIL>
   struct MultiPathCollection<T_HEAD, T_TAIL...> : MultiPathCollection<T_TAIL...>
   {
   protected:
      void init()
      {
         MultiPathCollection<T_TAIL...>::pushBackActionPath(path);
         MultiPathCollection<T_TAIL...>::init();
      }
   private:
      T_HEAD path;
   };

   template <>
   struct MultiPathCollection<> : SchedSwitchCaseAction
   {
   protected:
      void init() {}
   };

   template <typename... T_ACTION_PATHS>
   struct SWITCH__
         : MultiPathCollection< T_ACTION_PATHS...>
   {
       SWITCH__()
       {
          MultiPathCollection< T_ACTION_PATHS...>::init();
       }
   };
}

#endif /* SWITCHCASE11_H_ */
