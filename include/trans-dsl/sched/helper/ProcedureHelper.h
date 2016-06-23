/*
 * ProcedureHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PROCEDUREHELPER_H_
#define PROCEDUREHELPER_H_

#include <trans-dsl/sched/action/Procedure.h>
#include <trans-dsl/sched/action/NilFinalAction.h>
#include <trans-dsl/sched/action/Finally.h>

TSL_NS_BEGIN

namespace details
{
   template<typename T_ACTION, typename T_FINAL_ACTION, bool IS_PROTECTED>
   struct GenericProcedure: Procedure
   {
   private:
      OVERRIDE(bool isProtected() const)
      {
         return IS_PROTECTED;
      }
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
      IMPL_ROLE_WITH_VAR(FinalAction, T_FINAL_ACTION);
   };

   template<typename T_ACTION, typename T_FINAL_ACTION = NilFinalAction>
   struct PROCEDURE__ : GenericProcedure<T_ACTION, T_FINAL_ACTION, false>
   {
   };

   template<typename T_ACTION, typename T_FINAL_ACTION = NilFinalAction>
   struct PROTECTED_PROC__: GenericProcedure<T_ACTION, T_FINAL_ACTION, true>
   {
   };

   template <typename T_ACTION>
   struct FINALLY__ : Finally
   {
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

TSL_NS_END

/////////////////////////////////////////////////////////////////////////////
#define __procedure(...) \
       TSL_NS::details::PROCEDURE__< __VA_ARGS__ >

#define __prot_procedure(...) \
       TSL_NS::details::PROTECTED_PROC__< __VA_ARGS__ >

#define __finally(...) \
       TSL_NS::details::FINALLY__<__VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////

#endif /* PROCEDUREHELPER_H_ */
