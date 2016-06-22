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

#include <cub/dci/Role.h>
#include <cub/base/Status.h>

DEFINE_ROLE(RuntimeContext)
{
   ABSTRACT(void reportFailure(cub::Status));
   ABSTRACT(cub::Status getStatus() const);
};

#endif /* RUNTIMECONTEXT_H_ */
