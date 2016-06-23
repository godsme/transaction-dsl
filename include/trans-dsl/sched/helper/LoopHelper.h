/*
 * LoopHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LOOPHELPER_H_
#define LOOPHELPER_H_

#include <cub/mem/Placement.h>
#include "trans-dsl/sched/action/SchedLoopAction.h"
#include "trans-dsl/sched/concept/TransactionContext.h"

using cub::Placement;

TSL_NS_BEGIN

namespace details
{

   template <typename T_PRED, typename T_ACTION>
   struct LoopProcedure : private LoopCondCheckAction, Procedure
   {
      LoopProcedure(T_PRED& pred) : pred(pred) {}

   private:
      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
      IMPL_ROLE_WITH_TYPE(FinalAction, LoopCondCheckAction);
      OVERRIDE(bool isProtected() const)
      {
         return true;
      }

   private:
      OVERRIDE(bool shouldExecute(TransactionContext& context) const)
      {
         return pred(context.getTransactionInfo());
      }

      T_PRED& pred;
   };

   template <typename T_PRED, typename T_ACTION>
   struct GenericLoop : SchedLoopAction
   {
      GenericLoop() : cons(false) {}

   private:
      typedef LoopProcedure<T_PRED, T_ACTION> Proc;

   private:
      cub::Placement<Proc> proc;
      bool cons;

      OVERRIDE(void reset())
      {
         if(cons) proc.free();

         new (proc.alloc()) Proc(pred);

         cons = true;
      }

      ROLE_PROTO_TYPE(SchedAction)
      {
         return *proc;
      }

   protected:
      T_PRED pred;
   };


   /////////////////////////////////////////////////////////////
   template<typename T_PRED, typename T_ACTION>
   struct LOOP0__ : GenericLoop<T_PRED, T_ACTION>
   {
   private:
      typedef GenericLoop<T_PRED, T_ACTION> Parent;

      bool shouldExecute(TransactionContext& context)
      {
         return Parent::pred(context.getTransactionInfo());
      }
   };

   /////////////////////////////////////////////////////////////
   template<typename T_PRED, typename T_ACTION>
   struct LOOP1__ : GenericLoop<T_PRED, T_ACTION>
   {
   private:
      typedef GenericLoop<T_PRED, T_ACTION> Parent;

      bool shouldExecute(TransactionContext&)
      {
         return true;
      }
   };
}

TSL_NS_END

///////////////////////////////////////////////////////////////
#define __loop0(...) \
       TSL_NS::details::LOOP0__< __VA_ARGS__ >

#define __loop1(...) \
       TSL_NS::details::LOOP1__< __VA_ARGS__ >

///////////////////////////////////////////////////////////////

#endif /* LOOPHELPER_H_ */
