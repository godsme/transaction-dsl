/*
 * Transaction.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <base/dci/Role.h>
#include <base/Status.h>
#include "trans-dsl/utils/StopCause.h"

struct Event;

DEFINE_ROLE(Transaction)
{
   ABSTRACT(Status start());
   ABSTRACT(Status handleEvent(const Event&));
   ABSTRACT(Status stop(const StopCause& = StopCause()));
   ABSTRACT(void   kill(const StopCause& = StopCause()));

   Status start(const Event&);
};

#endif /* TRANSACTION_H_ */
