/*
 * MultiThreadScheduler.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADSCHEDULER_H_
#define MULTITHREADSCHEDULER_H_

#include <trans-dsl/utils/ActionStatus.h>
#include <trans-dsl/sched/def/ActionThreadDefs.h>
#include <trans-dsl/ext/multi-thread/concept/MultiThreadContext.h>
#include <trans-dsl/utils/SimpleRuntimeContext.h>
#include <cub/dci/Role.h>
#include <event/event.h>

FWD_DECL_EV(Event)

TSL_NS_BEGIN

struct TransactionContext;

struct MultiThreadScheduler
    : protected SimpleRuntimeContext
    , MultiThreadContext
{
   MultiThreadScheduler();

   cub::Status startMainThread(ActionThread&);
   cub::Status handleEvent(const ev::Event&);
   cub::Status stop(const cub::Status);
   void   kill(const cub::Status);

   bool isWorking() const;

private:
   OVERRIDE(cub::Status startThread(const ActionThreadId, ActionThread&, cub::Status& result));
   OVERRIDE(cub::Status killThread(const ActionThreadId, const cub::Status));
   OVERRIDE(cub::Status stopThread(const ActionThreadId, const cub::Status));
   OVERRIDE(cub::Status joinThread(const ActionThreadId, cub::Status& result) const);

private:
   cub::Status getFinalStatus() const;
   ActionStatus getMainThreadStatus() const;
   cub::Status finalProcess(ActionStatus status);
   void doStop(const cub::Status cause);
   cub::Status doHandleEvent(const ev::Event& event);
   void broadcastActionDone(const ActionThreadId, const cub::Status);
   void notifyActionDone(const ActionThreadId tid, const ActionThreadId who, const cub::Status result);
   void doneCheck(const ActionThreadId tid);

   void handleEventOnThread(const ActionThreadId tid, const ev::Event& event);
   void doKillThread(const ActionThreadId tid, const cub::Status cause);

private:

   struct NamedThread
   {
      NamedThread();

      cub::Status start(ActionThread& thread, MultiThreadScheduler& context);
      cub::Status handleEvent(MultiThreadScheduler& context, const ev::Event&);
      cub::Status stop(MultiThreadScheduler& context, const cub::Status cause);
      cub::Status kill(MultiThreadScheduler& context, const cub::Status cause);
      cub::Status getWorkingStatus() const;

   private:
      ActionThread* thread;
   }
   threads[MAX_NUM_OF_THREADS];

   ActionThreadId  current;
   bool stopping;

private:
   USE_ROLE(TransactionContext);
};

TSL_NS_END

#endif /* MULTITHREADSCHEDULER_H_ */
