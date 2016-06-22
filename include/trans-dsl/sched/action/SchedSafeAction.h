/*
 * SchedSafeAction.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSAFEACTION_H_
#define SCHEDSAFEACTION_H_

#include "trans-dsl/sched/concept/SchedAction.h"

TSL_NS_BEGIN

struct SchedSafeAction : SchedAction
{
   SchedSafeAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, cub::Status));
   OVERRIDE(void   kill(TransactionContext&, cub::Status));

private:
   cub::Status final(const cub::Status);

private:
   bool running;

private:
   USE_ROLE(SchedAction);
};

TSL_NS_END

#endif /* SCHEDSAFEACTION_H_ */
