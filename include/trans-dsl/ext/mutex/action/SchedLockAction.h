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

#include "trans-dsl/sched/concept/SchedAction.h"
#include <trans-dsl/ext/mutex/concept/TransMutextId.h>

struct SchedLockAction : SchedAction
{
   SchedLockAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, Status));
   OVERRIDE(void   kill(TransactionContext&, Status));

private:
   Status final(Status, TransactionContext&);
   Status lock(TransactionContext&);
   Status unlock(TransactionContext&);
   Status tryExec(TransactionContext&, const Event&);

private:
   bool waiting;

private:
   USE_ROLE(SchedAction);
   ABSTRACT(TransMutexId getMutexId() const);
};

#endif /* SCHEDLOCKACTION_H_ */
