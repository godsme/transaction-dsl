/*
 * LockHelper.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LOCKHELPER_H_
#define LOCKHELPER_H_

#include "trans-dsl/ext/mutex/action/SchedLockAction.h"

TSL_NS_BEGIN

namespace details
{
   template<TransMutexId MUTEX_ID, typename T_ACTION>
   struct LOCK__: SchedLockAction
   {
   private:
      OVERRIDE(TransMutexId getMutexId() const)
      {
         return MUTEX_ID;
      }

      IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
}

TSL_NS_END

/////////////////////////////////////////////////////////
#define __lock(...) TSL_NS::details::LOCK__< __VA_ARGS__ >
/////////////////////////////////////////////////////////

#endif /* LOCKHELPER_H_ */
