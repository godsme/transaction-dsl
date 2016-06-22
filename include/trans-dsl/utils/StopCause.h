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

#include <cub/base/Status.h>
#include <trans-dsl/tsl.h>

TSL_NS_BEGIN

struct StopCause
{
   StopCause();
   StopCause(const cub::Status cause);

   operator cub::Status() const;

private:
   cub::Status cause;
};

TSL_NS_END

#endif /* STOPCAUSE_H_ */
