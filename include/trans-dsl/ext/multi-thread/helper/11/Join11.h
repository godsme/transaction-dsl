/*
 * Join11.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef JOIN11_H_
#define JOIN11_H_

#include "trans-dsl/ext/multi-thread/action/SchedJoinAction.h"

namespace details
{
   template <ActionThreadId... T_TIDS> struct ThreadAdder;

   template <ActionThreadId T_HEAD, ActionThreadId... T_TAIL>
   struct ThreadAdder<T_HEAD, T_TAIL...>
   {
      void operator()(SchedJoinAction& actions) const
      {
         actions.addJoinThread(T_HEAD);
         ThreadAdder<T_TAIL...>()(actions);
      }
   };

   template <> struct ThreadAdder<>
   {
      void operator()(SchedJoinAction&) const {}
   };

   template <ActionThreadId... T_TIDS>
   struct JOIN__ : SchedJoinAction
   {
       JOIN__()
       {
          ThreadAdder< T_TIDS...>()(*this);
       }
   };
}

#endif /* JOIN11_H_ */
