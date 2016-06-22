/*
 * SchedLockAction.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDLOCKACTION_H_
#define SCHEDLOCKACTION_H_

#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/ext/mutex/concept/TransMutextId.h>

TSL_NS_BEGIN

struct SchedLockAction : SchedAction
{
   SchedLockAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, cub::Status));
   OVERRIDE(void   kill(TransactionContext&, cub::Status));

private:
   cub::Status final(cub::Status, TransactionContext&);
   cub::Status lock(TransactionContext&);
   cub::Status unlock(TransactionContext&);
   cub::Status tryExec(TransactionContext&, const ev::Event&);

private:
   bool waiting;

private:
   USE_ROLE(SchedAction);
   ABSTRACT(TransMutexId getMutexId() const);
};

TSL_NS_END

#endif /* SCHEDLOCKACTION_H_ */
