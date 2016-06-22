/*
 * GofState.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef GOFSTATE_H_
#define GOFSTATE_H_

#include <cub/gof/Singleton.h>
#include <cub/base/Keywords.h>
#include <trans-dsl/utils/ActionStatus.h>

FWD_DECL_EV(Event);

TSL_NS_BEGIN

struct TransactionContext;

template <typename T>
struct GofState
{
   virtual ~GofState() {}

   virtual cub::Status enter(T&, TransactionContext&, const ActionStatus status)
   {
      return status;
   }

   virtual cub::Status exec(T&, TransactionContext&)
   {
      return TSL_FATAL_BUG;
   }

   virtual cub::Status handleEvent(T&, TransactionContext&, const ev::Event&)
   {
      return TSL_UNKNOWN_EVENT;
   }

   virtual cub::Status stop(T&, TransactionContext&, const cub::Status)
   {
      return TSL_SUCCESS;
   }

   virtual void   kill(T&, TransactionContext&, const cub::Status)
   {
   }
};

TSL_NS_END

#define __DEF_STATE_INTERFACE(object) \
     struct object::State : GofState<object>

#define __DECL_STATE_INTERFACE(object)   \
    __DEF_STATE_INTERFACE(object) {}

///////////////////////////////////////////////////////////////////
#define __DEF_BASE_STATE_CLASS(object, S) \
struct object::S : object::State

#define __DEF_DERIVED_STATE_CLASS(object, S, base) \
    DEF_SINGLETON(object::S) EXTENDS(object::base)

#define __DEF_STATE_CLASS(object, S) \
   __DEF_DERIVED_STATE_CLASS(object, S, State)

#define __DEF_BASE_STATE(object, S) \
struct object::S : object::State

///////////////////////////////////////////////////////////////////
#define ____GOTO_STATE(S, status) goto##S##State(context, status)
#define __GOTO_STATE(S) ____GOTO_STATE(S, status)

#define __DEF_STATE(object, S) \
Status object::goto##S##State(TransactionContext& context, const cub::Status status) \
{                                                                                    \
   state = &S::getInstance();                                                        \
   return state->enter(*this, context, status);                                      \
}

#endif /* GOFSTATE_H_ */
