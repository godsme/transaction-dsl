/*
 * ThrowHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef THROWHELPER_H_
#define THROWHELPER_H_

#include "trans-dsl/sched/action/SchedThrowAction.h"

TSL_NS_BEGIN

namespace details
{
   template <cub::Status V_STATUS = TSL_RESERVED_FAILURE>
   struct THROW__ : SchedThrowAction
   {
   private:
      OVERRIDE(cub::Status getStatus() const)
      {
         return V_STATUS;
      }
   };
}

TSL_NS_END

////////////////////////////////////////////////////////////////
#define __throw(...) tsl::details::THROW__< __VA_ARGS__ >

#define __nop() __throw(SUCCESS)

////////////////////////////////////////////////////////////////

#endif /* THROWHELPER_H_ */
