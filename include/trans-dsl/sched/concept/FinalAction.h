/*
 * FinalAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FINALACTION_H_
#define FINALACTION_H_

#include <base/dci/Role.h>
#include <base/Status.h>

struct TransactionContext;
struct Event;

DEFINE_ROLE(FinalAction)
{
   ABSTRACT(Status exec(TransactionContext&));
   ABSTRACT(Status handleEvent(TransactionContext&, const Event&));
   ABSTRACT(void   kill(TransactionContext&, const Status));
};

#endif /* FINALACTION_H_ */
