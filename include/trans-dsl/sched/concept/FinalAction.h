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

#include <event/event.h>
#include <trans-dsl/tsl.h>
#include <trans-dsl/TslStatus.h>

#include <cub/dci/Role.h>

FWD_DECL_EV(Event);

TSL_NS_BEGIN

struct TransactionContext;

DEFINE_ROLE(FinalAction)
{
   ABSTRACT(cub::Status exec(TransactionContext&));
   ABSTRACT(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   ABSTRACT(void   kill(TransactionContext&, const cub::Status));
};

TSL_NS_END

#endif /* FINALACTION_H_ */
