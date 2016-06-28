/*
 * ExclusiveHelper.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef EXCLUSIVEHELPER_H_
#define EXCLUSIVEHELPER_H_

#include <trans-dsl/sched/action/SchedExclusiveAction.h>
#include <trans-dsl/utils/ActionMacroHelper.h>
#include <trans-dsl/sched/helper/LinkedHelper.h>

TSL_NS_BEGIN

////////////////////////////////////////////////////////////////
#define __EXCLUSIVE_ADD_ACTION(n)  addAction(action ## n);
#define EXCLUSIVE_ADD_ACTION(n)    SIMPLE_REPEAT(n, __EXCLUSIVE_ADD_ACTION)

////////////////////////////////////////////////////////////////
#define __EXCLUSIVE_PARTIAL_COLLECTION(n)                          \
namespace details {                                                \
template < DECL_TEMPLATE_ARGS(n)>                                  \
struct ExclusiveActions __PARTIAL_5_##n(ACTION_ARGS, DUMMY_ARGS)   \
   : SchedExclusiveAction                                          \
{                                                                  \
   ExclusiveActions()                                              \
   { EXCLUSIVE_ADD_ACTION(n) }                                     \
private:                                                           \
    DECL_MEMBERS(n)                                                \
};                                                                 \
}


__EXCLUSIVE_PARTIAL_COLLECTION(5)
__EXCLUSIVE_PARTIAL_COLLECTION(4)
__EXCLUSIVE_PARTIAL_COLLECTION(3)
__EXCLUSIVE_PARTIAL_COLLECTION(2)
__EXCLUSIVE_PARTIAL_COLLECTION(1)


/////////////////////////////////////////////////////////////////////////////////
#define __DEF_GENERIC_EXCLUSIVE_ACTION(n)         \
namespace details {                               \
   template <DECL_DUMMY_DEFAULT(n)>               \
   struct EXCLUSIVE__                             \
        : ExclusiveActions<DECL_ALL_ARGS(n)>      \
   {                                              \
   };                                             \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_GENERIC_EXCLUSIVE_ACTION(5);

/////////////////////////////////////////////////////////////////////////////////
#define __exclusive(...) \
       TSL_NS::details::EXCLUSIVE__< __VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////////

TSL_NS_END

#endif /* EXCLUSIVEHELPER_H_ */
