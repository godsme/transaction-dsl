/*
 * SwitchCase98.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SWITCHCASE98_H_
#define SWITCHCASE98_H_

#include "trans-dsl/sched/action/SchedSwitchCaseAction.h"
#include <trans-dsl/utils/DummyAction.h>

namespace details
{
   template <typename ACTION_PATH1, typename ACTION_PATH2, typename ACTION_PATH3>
   struct MultiPathCollection : SchedSwitchCaseAction
   {
      MultiPathCollection()
      {
         pushBackActionPath(path1);
         pushBackActionPath(path2);
         pushBackActionPath(path3);
      }

   private:
      ACTION_PATH1 path1;
      ACTION_PATH2 path2;
      ACTION_PATH3 path3;
   };

   template <typename ACTION_PATH1, typename ACTION_PATH2>
   struct MultiPathCollection<ACTION_PATH1, ACTION_PATH2, DummyAction>
      : SchedSwitchCaseAction
   {
      MultiPathCollection()
      {
         pushBackActionPath(path1);
         pushBackActionPath(path2);
      }

   private:
      ACTION_PATH1 path1;
      ACTION_PATH2 path2;
   };

   template <typename ACTION_PATH1>
   struct MultiPathCollection<ACTION_PATH1, DummyAction, DummyAction>
      : SchedSwitchCaseAction
   {
      MultiPathCollection()
      {
         pushBackActionPath(path1);
      }

   private:
      ACTION_PATH1 path1;
   };

   /////////////////////////////////////////////////////////////////////
   template < typename ACTION_PATH1
            , typename ACTION_PATH2 = DummyAction
            , typename ACTION_PATH3 = DummyAction>
   struct SWITCH__
      : MultiPathCollection
          < ACTION_PATH1
          , ACTION_PATH2
          , ACTION_PATH3>
   {
   };
}

#endif /* SWITCHCASE98_H_ */
