/*
 * Sequential98.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SEQUENTIAL98_H_
#define SEQUENTIAL98_H_

#include "trans-dsl/sched/action/SchedSequentialAction.h"
#include "trans-dsl/sched/helper/LinkedHelper.h"
#include "trans-dsl/sched/helper/VoidHelper.h"
#include "trans-dsl/utils/ActionMacroHelper.h"

TSL_NS_BEGIN

////////////////////////////////////////////////////////////////
#define __PUSH_BACK_ACTION(n)  pushBackAction(action ## n);
#define PUSH_BACK_ACTIONS(n) SIMPLE_REPEAT(n, __PUSH_BACK_ACTION)

////////////////////////////////////////////////////////////////
#define __SEQ_PARTIAL_COLLECTION(n)                                \
namespace details {                                                \
template < DECL_TEMPLATE_ARGS(n)>                                  \
struct SequentialActions __PARTIAL_30_##n(ACTION_ARGS, DUMMY_ARGS) \
   : SchedSequentialAction                                         \
{                                                                  \
   SequentialActions()                                             \
   { PUSH_BACK_ACTIONS(n) }                                        \
private:                                                           \
    DECL_MEMBERS(n)                                                \
};                                                                 \
}

////////////////////////////////////////////////////////////////
__SEQ_PARTIAL_COLLECTION(30)
__SEQ_PARTIAL_COLLECTION(29)
__SEQ_PARTIAL_COLLECTION(28)
__SEQ_PARTIAL_COLLECTION(27)
__SEQ_PARTIAL_COLLECTION(26)
__SEQ_PARTIAL_COLLECTION(25)
__SEQ_PARTIAL_COLLECTION(24)
__SEQ_PARTIAL_COLLECTION(23)
__SEQ_PARTIAL_COLLECTION(22)
__SEQ_PARTIAL_COLLECTION(21)
__SEQ_PARTIAL_COLLECTION(20)
__SEQ_PARTIAL_COLLECTION(19)
__SEQ_PARTIAL_COLLECTION(18)
__SEQ_PARTIAL_COLLECTION(17)
__SEQ_PARTIAL_COLLECTION(16)
__SEQ_PARTIAL_COLLECTION(15)
__SEQ_PARTIAL_COLLECTION(14)
__SEQ_PARTIAL_COLLECTION(13)
__SEQ_PARTIAL_COLLECTION(12)
__SEQ_PARTIAL_COLLECTION(11)
__SEQ_PARTIAL_COLLECTION(10)
__SEQ_PARTIAL_COLLECTION(9)
__SEQ_PARTIAL_COLLECTION(8)
__SEQ_PARTIAL_COLLECTION(7)
__SEQ_PARTIAL_COLLECTION(6)
__SEQ_PARTIAL_COLLECTION(5)
__SEQ_PARTIAL_COLLECTION(4)
__SEQ_PARTIAL_COLLECTION(3)
__SEQ_PARTIAL_COLLECTION(2)
__SEQ_PARTIAL_COLLECTION(1)

/////////////////////////////////////////////////////////////////////////////////
#define __DEF_GENERIC_SEQUANTIAL_ACTION(n)        \
namespace details {                               \
   template <DECL_DUMMY_DEFAULT(n)>               \
   struct SEQUENTIAL__                            \
        : SequentialActions<DECL_ALL_ARGS(n)>     \
   {                                              \
   };                                             \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_GENERIC_SEQUANTIAL_ACTION(30);


////////////////////////////////////////////////////////////////
#define __VOID_MEMBER_DEF(n)  tsl::details::LINKED__< tsl::details::VOID__< __ARG(n) > > action ## n;
#define DECL_VOID_MEMBERS(n) SIMPLE_REPEAT(n, __VOID_MEMBER_DEF)

////////////////////////////////////////////////////////////////
#define __VOID_SEQ_PARTIAL_COLLECTION(n)                           \
namespace details {                                                \
template < DECL_TEMPLATE_ARGS(n)>                                  \
struct VoidSequentialActions                                       \
   __PARTIAL_30_##n(ACTION_ARGS, DUMMY_ARGS)                       \
   : SchedSequentialAction                                         \
{                                                                  \
   VoidSequentialActions()                                         \
   { PUSH_BACK_ACTIONS(n) }                                        \
private:                                                           \
   DECL_VOID_MEMBERS(n)                                            \
};                                                                 \
}

////////////////////////////////////////////////////////////////
__VOID_SEQ_PARTIAL_COLLECTION(30)
__VOID_SEQ_PARTIAL_COLLECTION(29)
__VOID_SEQ_PARTIAL_COLLECTION(28)
__VOID_SEQ_PARTIAL_COLLECTION(27)
__VOID_SEQ_PARTIAL_COLLECTION(26)
__VOID_SEQ_PARTIAL_COLLECTION(25)
__VOID_SEQ_PARTIAL_COLLECTION(24)
__VOID_SEQ_PARTIAL_COLLECTION(23)
__VOID_SEQ_PARTIAL_COLLECTION(22)
__VOID_SEQ_PARTIAL_COLLECTION(21)
__VOID_SEQ_PARTIAL_COLLECTION(20)
__VOID_SEQ_PARTIAL_COLLECTION(19)
__VOID_SEQ_PARTIAL_COLLECTION(18)
__VOID_SEQ_PARTIAL_COLLECTION(17)
__VOID_SEQ_PARTIAL_COLLECTION(16)
__VOID_SEQ_PARTIAL_COLLECTION(15)
__VOID_SEQ_PARTIAL_COLLECTION(14)
__VOID_SEQ_PARTIAL_COLLECTION(13)
__VOID_SEQ_PARTIAL_COLLECTION(12)
__VOID_SEQ_PARTIAL_COLLECTION(11)
__VOID_SEQ_PARTIAL_COLLECTION(10)
__VOID_SEQ_PARTIAL_COLLECTION(9)
__VOID_SEQ_PARTIAL_COLLECTION(8)
__VOID_SEQ_PARTIAL_COLLECTION(7)
__VOID_SEQ_PARTIAL_COLLECTION(6)
__VOID_SEQ_PARTIAL_COLLECTION(5)
__VOID_SEQ_PARTIAL_COLLECTION(4)
__VOID_SEQ_PARTIAL_COLLECTION(3)
__VOID_SEQ_PARTIAL_COLLECTION(2)
__VOID_SEQ_PARTIAL_COLLECTION(1)

/////////////////////////////////////////////////////////////////////////////////
#define __DEF_VOID_SEQUANTIAL_ACTION(n)           \
namespace details {                               \
   template <DECL_DUMMY_DEFAULT(n)>               \
   struct VOID_SEQUENTIAL__                       \
        : VoidSequentialActions<DECL_ALL_ARGS(n)> \
   {                                              \
   };                                             \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_VOID_SEQUANTIAL_ACTION(30);

TSL_NS_END

#endif /* SEQUENTIAL98_H_ */
