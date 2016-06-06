/*
 * ActionStatus.cc
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "trans-dsl/utils/ActionStatus.h"

ActionStatus::ActionStatus(Status status)
   : status(status)
{
}

bool ActionStatus::isWorking() const
{
   return status == CONTINUE || status == UNKNOWN_EVENT;
}

bool ActionStatus::isFailed() const
{
   return IS_FAILED_STATUS(status);
}

bool ActionStatus::eventAccepted() const
{
   return status != UNKNOWN_EVENT;
}

bool ActionStatus::eventNotAccepted() const
{
   return !eventAccepted();
}

ActionStatus::operator Status() const
{
   return status;
}

bool ActionStatus::isDone() const
{
   return status == SUCCESS;
}
