/*
 * StopCause.cc
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/utils/StopCause.h"
#include "trans-dsl/utils/ActionStatus.h"

StopCause::StopCause() : cause(FORCE_STOPPED)
{
}

StopCause::StopCause(const Status cause)
      : cause(ActionStatus(cause).isFailed() ? cause : FORCE_STOPPED)
{
}

StopCause::operator Status() const
{
   return cause;
}
