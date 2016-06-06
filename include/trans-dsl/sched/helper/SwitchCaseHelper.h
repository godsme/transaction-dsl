/*
 * SwitchCaseHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SWITCHCASEHELPER_H_
#define SWITCHCASEHELPER_H_

#include "trans-dsl/sched/action/ActionPath.h"

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include "trans-dsl/sched/helper/11/SwitchCase11.h"
#else
#include "trans-dsl/sched/helper/98/SwitchCase98.h"
#endif

namespace details
{
   template <typename PRED, typename T_ACTION>
   struct CASE__ : ActionPath
   {
      OVERRIDE(bool shouldExecute(const TransactionInfo& info))
      {
         return pred(info);
      }

      OVERRIDE(SchedAction& getAction())
      {
         return action;
      }

   private:
      T_ACTION action;
      PRED pred;
   };

   template <typename PRED, typename T_ACTION>
   struct OPTIONAL__
      : SWITCH__< CASE__<PRED, T_ACTION> >
   {
   };
}

//////////////////////////////////////////////////////////////////
#define __switch(...) \
       details::SWITCH__< __VA_ARGS__ >

#define __case(...) \
       details::CASE__< __VA_ARGS__ >

#define __optional(...) details::OPTIONAL__< __VA_ARGS__ >

//////////////////////////////////////////////////////////////////

#endif /* SWITCHCASEHELPER_H_ */
