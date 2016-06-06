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

namespace details
{
   template <Status V_STATUS = RESERVED_FAILURE>
   struct THROW__ : SchedThrowAction
   {
   private:
      OVERRIDE(Status getStatus() const)
      {
         return V_STATUS;
      }
   };
}

////////////////////////////////////////////////////////////////
#define __throw(...) details::THROW__< __VA_ARGS__ >

#define __nop() __throw(SUCCESS)

////////////////////////////////////////////////////////////////

#endif /* THROWHELPER_H_ */
