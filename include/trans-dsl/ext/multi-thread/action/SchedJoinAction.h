/*
 * SchedJoinAction.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDJOINACTION_H_
#define SCHEDJOINACTION_H_

#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/sched/def/ActionThreadDefs.h>
#include <trans-dsl/ext/multi-thread/concept/ActionThreadId.h>

TSL_NS_BEGIN

struct SchedJoinAction : SchedAction
{
   SchedJoinAction();

   OVERRIDE(cub::Status exec(TransactionContext&));
   OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
   OVERRIDE(cub::Status stop(TransactionContext&, cub::Status));
   OVERRIDE(void        kill(TransactionContext&, cub::Status));

   cub::Status addJoinThread(const ActionThreadId threadId);

private:
   typedef ThreadBitmapType HostType;

private:
   bool isWaiting(const ActionThreadId threadId) const;
   void addThread(const ActionThreadId threadId);
   void threadDone(const ActionThreadId threadId);

   cub::Status reschedule();
   cub::Status join(const ActionThreadId threadId,
            TransactionContext& context);
   cub::Status onThreadDone(const ActionThreadId tid, const cub::Status);

private:
   HostType joinPointBitmap;
};

TSL_NS_END

#endif /* SCHEDJOINACTION_H_ */
