/*
 * RuntimeContext.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RUNTIMECONTEXT_H_
#define RUNTIMECONTEXT_H_

#include <trans-dsl/tsl.h>

#include <cub/dci/Role.h>
#include <cub/base/Status.h>

TSL_NS_BEGIN

DEFINE_ROLE(RuntimeContext)
{
   ABSTRACT(void reportFailure(cub::Status));
   ABSTRACT(cub::Status getStatus() const);
};

TSL_NS_END

#endif /* RUNTIMECONTEXT_H_ */
