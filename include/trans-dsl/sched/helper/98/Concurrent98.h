/*
 * Concurrent98.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef CONCURRENT98_H_
#define CONCURRENT98_H_

#include "trans-dsl/sched/action/SchedConcurrentAction.h"
#include "trans-dsl/sched/helper/LinkedThreadHelper.h"
#include "trans-dsl/sched/helper/VoidHelper.h"
#include "trans-dsl/utils/ActionMacroHelper.h"

////////////////////////////////////////////////////////////////
#define __THREAD_DEF(n)  details::LINKED_THREAD__< __ARG(n) > action ## n;

#define DECL_THREADS(n) SIMPLE_REPEAT(n, __THREAD_DEF)

////////////////////////////////////////////////////////////////
#define __ADD_THREAD(n)  addThread(action ## n);
#define ADD_THREADS(n) SIMPLE_REPEAT(n, __ADD_THREAD)

SchedConcurrentAction a;
////////////////////////////////////////////////////////////////
#define __CON_PARTIAL_COLLECTION(n)                                 \
namespace details {                                                 \
  template < DECL_TEMPLATE_ARGS(n)>                                 \
  struct ConcurrentActions __PARTIAL_5_##n(ACTION_ARGS, DUMMY_ARGS) \
     : SchedConcurrentAction                                        \
  {                                                                 \
     ConcurrentActions()                                            \
     { ADD_THREADS(n) }                                             \
  private:                                                          \
      DECL_THREADS(n)                                               \
  };                                                                \
}

/////////////////////////////////////////////////////////////////////////////////
__CON_PARTIAL_COLLECTION(5)
__CON_PARTIAL_COLLECTION(4)
__CON_PARTIAL_COLLECTION(3)
__CON_PARTIAL_COLLECTION(2)

/////////////////////////////////////////////////////////////////////////////////
#define __DEF_GENERIC_CONCURRENT_ACTION(n)   \
namespace details                            \
{                                            \
   template <DECL_DUMMY_DEFAULT(n)>          \
   struct CONCURRENT__ :                     \
       ConcurrentActions<DECL_ALL_ARGS(n)>   \
   {                                         \
   };                                        \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_GENERIC_CONCURRENT_ACTION(5);


////////////////////////////////////////////////////////////////
#define __VOID_THREAD_DEF(n)  \
details::LINKED_THREAD__< details::VOID__< __ARG(n) > > action ## n;

#define DECL_VOID_THREADS(n) SIMPLE_REPEAT(n, __VOID_THREAD_DEF)

////////////////////////////////////////////////////////////////
#define __VOID_CON_PARTIAL_COLLECTION(n)                            \
namespace details {                                                 \
  template < DECL_TEMPLATE_ARGS(n)>                                 \
  struct VoidConcurrentActions                                      \
      __PARTIAL_5_##n(ACTION_ARGS, DUMMY_ARGS)                      \
     : SchedConcurrentAction                                        \
  {                                                                 \
     VoidConcurrentActions()                                        \
     { ADD_THREADS(n) }                                             \
  private:                                                          \
      DECL_VOID_THREADS(n)                                          \
  };                                                                \
}

/////////////////////////////////////////////////////////////////////////////////
__VOID_CON_PARTIAL_COLLECTION(5)
__VOID_CON_PARTIAL_COLLECTION(4)
__VOID_CON_PARTIAL_COLLECTION(3)
__VOID_CON_PARTIAL_COLLECTION(2)

/////////////////////////////////////////////////////////////////////////////////
#define __DEF_VOID_CONCURRENT_ACTION(n)         \
namespace details                               \
{                                               \
   template <DECL_DUMMY_DEFAULT(n)>             \
   struct VOID_CONCURRENT__ :                   \
       VoidConcurrentActions<DECL_ALL_ARGS(n)>  \
   {                                            \
   };                                           \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_VOID_CONCURRENT_ACTION(5);
#endif /* CONCURRENT98_H_ */
