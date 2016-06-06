/*
 * Join98.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef JOIN98_H_
#define JOIN98_H_

#include "trans-dsl/ext/multi-thread/action/SchedJoinAction.h"
#include "trans-dsl/utils/ActionMacroHelper.h"

#define __TID(n)   TID ## n

/////////////////////////////////////////////////////////////////////////////////////
#define __ACTION_THREAD_ARG(n)    ActionThreadId __TID(n)
#define __ACTION_THREAD_ARGS(n)   __ACTION_THREAD_ARG(n),
#define __DECL_ACTION_THREAD_ARGS(n) REPEAT(n, __ACTION_THREAD_ARGS, __ACTION_THREAD_ARG)
/////////////////////////////////////////////////////////////////////////////////////

#define __DO_ADD_JOIN_POINT(n) joinPointAction.addJoinThread(__TID(n));
#define __ADD_JOIN_POINT(n) SIMPLE_REPEAT(n, __DO_ADD_JOIN_POINT)

#define __JOIN_POINT_ADDER(n) \
template <__DECL_ACTION_THREAD_ARGS(n)> \
struct JoinPointAdder \
{ }

/////////////////////////////////////////////////////////////////////////////////////
#define __INST_TID(n)      __TID(n),
#define __INST_TIDS(n) REPEAT(n, __INST_TID, __TID)

/////////////////////////////////////////////////////////////////////////////////////
#define __INST_INVALID_TID(n) , NIL_TID

#define __INST_INVALID_TIDS(n) SIMPLE_REPEAT(n, __INST_INVALID_TID)
/////////////////////////////////////////////////////////////////////////////////////
//<__INST_TIDS(n) __INST_INVALID_TIDS(m)>

#define __JOIN_POINT_PARTIAL_ADDER(n)                     \
template <__DECL_ACTION_THREAD_ARGS(n)>                      \
struct JoinPointAdder __PARTIAL_7_##n (__INST_TIDS, __INST_INVALID_TIDS) \
{                                                            \
   void operator()(SchedJoinAction& joinPointAction)         \
   {                                                         \
      __ADD_JOIN_POINT(n)                                    \
   }                                                         \
}

/////////////////////////////////////////////////////////////////////////////////////
__JOIN_POINT_PARTIAL_ADDER(7);
__JOIN_POINT_PARTIAL_ADDER(6);
__JOIN_POINT_PARTIAL_ADDER(5);
__JOIN_POINT_PARTIAL_ADDER(4);
__JOIN_POINT_PARTIAL_ADDER(3);
__JOIN_POINT_PARTIAL_ADDER(2);
__JOIN_POINT_PARTIAL_ADDER(1);

/////////////////////////////////////////////////////////////////////////////////////
#define __DEFAULT_THREAD_ARG(n)    ActionThreadId __TID(n) = NIL_TID
#define __DEFAULT_THREAD_ARGS(n)   __DEFAULT_THREAD_ARG(n),
#define __DECL_DEFAULT_THREAD_ARGS(n) REPEAT(n, __DEFAULT_THREAD_ARGS, __DEFAULT_THREAD_ARG)

#define __INST_TIDS_ONLY(n) REPEAT(n, __INST_TID, __TID)

/////////////////////////////////////////////////////////////////////////////////////
#define __GENERIC_JOINT_POINT_ACTION(n)              \
namespace details                                    \
{                                                    \
  template <__DECL_DEFAULT_THREAD_ARGS(n)>           \
  struct JOIN__ : SchedJoinAction                    \
  {                                                  \
     JOIN__()                                        \
     {                                               \
       JoinPointAdder<__INST_TIDS_ONLY(n)>()(*this); \
     }                                               \
  };                                                 \
}

__GENERIC_JOINT_POINT_ACTION(7)

#endif /* JOIN98_H_ */
