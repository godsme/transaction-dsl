/*
 * StopCause.h
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef STOPCAUSE_H_
#define STOPCAUSE_H_

#include <base/Status.h>

struct StopCause
{
   StopCause();
   StopCause(const Status cause);

   operator Status() const;

private:
   Status cause;
};

#endif /* STOPCAUSE_H_ */
