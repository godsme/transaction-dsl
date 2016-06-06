/*
 * ActionStatus.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONSTATUS_H_
#define ACTIONSTATUS_H_

#include <base/Status.h>

struct ActionStatus
{
   ActionStatus(Status status);

   bool isWorking() const;
   bool isFailed() const;
   bool isDone() const;
   bool eventAccepted() const;
   bool eventNotAccepted() const;

   operator Status() const;

private:
   Status status;
};

#endif /* ACTIONSTATUS_H_ */
