/*
 * SchedTimerProtAction.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDTIMERPROTACTION_H_
#define SCHEDTIMERPROTACTION_H_

#include <trans-dsl/sched/concept/SchedAction.h>
#include <trans-dsl/utils/DeclState.h>

TSL_NS_BEGIN

struct RelativeTimer;

namespace details
{
   struct TimerProtActionState
   {
      TimerProtActionState();

      void start();
      void stop(const cub::Status status);

      bool isStopping() const;
      bool isDone() const;

   private:
      enum
      {
         IDLE,
         WORKING,
         STOPPING,
      }state;
   };

   struct TimerProtAction : SchedAction
   {
      OVERRIDE(cub::Status exec(TransactionContext&));
      OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
      OVERRIDE(cub::Status stop(TransactionContext&, const cub::Status));
      OVERRIDE(void   kill(TransactionContext&, const cub::Status));

   private:
      cub::Status startTimer(TransactionContext&);

   private:
      USE_ROLE(RelativeTimer);
      USE_ROLE(SchedAction);
      USE_ROLE(TimerProtActionState);

      ABSTRACT(cub::Status getTimeoutStatus() const);
   };

   struct TimerProtFinalAction : FinalAction
   {
      OVERRIDE(cub::Status exec(TransactionContext&));
      OVERRIDE(cub::Status handleEvent(TransactionContext&, const ev::Event&));
      OVERRIDE(void   kill(TransactionContext&, const cub::Status));

   private:
      USE_ROLE(SchedAction);
      USE_ROLE(TimerProtActionState);
   };
}

TSL_NS_END

#endif /* SCHEDTIMERPROTACTION_H_ */
