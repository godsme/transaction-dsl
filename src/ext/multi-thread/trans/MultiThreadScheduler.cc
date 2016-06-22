/*
 * MultiThreadScheduler.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include <trans-dsl/ext/multi-thread/trans/MultiThreadScheduler.h>
#include <trans-dsl/sched/action/ActionThread.h>
#include <trans-dsl/ext/multi-thread/def/ThreadDoneMsg.h>
#include <event/impl/ConsecutiveEventInfo.h>
#include <event/concept/Event.h>
#include <cub/base/Assertions.h>
#include <trans-dsl/utils/SimpleRuntimeContextAutoSwitch.h>

TSL_NS_BEGIN

/////////////////////////////////////////////////////////////////
MultiThreadScheduler::NamedThread::NamedThread()
   : thread(0)
{
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::NamedThread::start(ActionThread& newThread, MultiThreadScheduler& scheduler)
{
   if(scheduler.stopping)
   {
      return TSL_FAILED;
   }

   if(thread != 0)
   {
      return TSL_DUPTID;
   }

   thread = &newThread;

   (void) thread->exec(scheduler.ROLE(TransactionContext));

   return TSL_SUCCESS;
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::NamedThread::handleEvent(MultiThreadScheduler& scheduler, const ev::Event& event)
{
   if(thread == 0 || !thread->isWorking())
   {
      return TSL_UNKNOWN_EVENT;
   }

   return thread->handleEvent(scheduler.ROLE(TransactionContext), event);
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::NamedThread::stop(MultiThreadScheduler& scheduler, const cub::Status cause)
{
   if(thread == 0 || !thread->isWorking())
   {
      return TSL_UNKNOWN_EVENT;
   }

   return thread->stop(scheduler.ROLE(TransactionContext), cause);
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::NamedThread::kill(MultiThreadScheduler& scheduler, const cub::Status cause)
{
   if(thread == 0 || !thread->isWorking())
   {
      return TSL_CONTINUE;
   }

   thread->kill(scheduler.ROLE(TransactionContext), cause);

   return TSL_SUCCESS;
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::NamedThread::getWorkingStatus() const
{
   if (thread == 0 || thread->isWorking())
   {
      return TSL_CONTINUE;
   }

   return thread->getStatus();
}

/////////////////////////////////////////////////////////////////
MultiThreadScheduler::MultiThreadScheduler()
  : current(NIL_TID)
  , stopping(false)
{
}

/////////////////////////////////////////////////////////////////
namespace
{
   struct AutoThreadSwitch
   {
      AutoThreadSwitch(const ActionThreadId newThread, ActionThreadId& current)
         : original(current)
         , current(current)
      {
         current = newThread;
      }

      ~AutoThreadSwitch()
      {
         current = original;
      }

   private:
      ActionThreadId original;
      ActionThreadId& current;
   };
}

/////////////////////////////////////////////////////////////////
#define FOREACH_THREAD(tid) \
   for(ActionThreadId tid = 0; tid < MAX_NUM_OF_THREADS; ++tid)

/////////////////////////////////////////////////////////////////
void MultiThreadScheduler::doneCheck(const ActionThreadId tid)
{
   ActionStatus status = threads[tid].getWorkingStatus();
   if (!status.isWorking())
   {
      broadcastActionDone(tid, status);
   }
}

/////////////////////////////////////////////////////////////////
void MultiThreadScheduler::notifyActionDone(const ActionThreadId tid, const ActionThreadId who, const cub::Status result)
{
   if(tid == who) return;

   (void) handleEventOnThread(tid, ev::ConsecutiveEventInfo(EV_ACTION_THREAD_DONE, ThreadDoneMsg(who, result)));
}

/////////////////////////////////////////////////////////////////
void MultiThreadScheduler::broadcastActionDone(const ActionThreadId who, const cub::Status result)
{
   FOREACH_THREAD(tid)
   {
      notifyActionDone(tid, who, result);
   }
}

namespace
{
   struct AutoContextSwitch : SimpleRuntimeContextAutoSwitch
   {
      AutoContextSwitch(RuntimeContext& __THIS__, TransactionContext& context)
           : SimpleRuntimeContextAutoSwitch(__THIS__, context)
      {
      }
   };
}

#define SWITCH_TO(tid) \
   AutoThreadSwitch autoSwitch(tid, current); \
   AutoContextSwitch autoContextSwitch(*this, ROLE(TransactionContext))

/////////////////////////////////////////////////////////////////
#define CHECK_TID_SCOPE(tid)  \
   if (tid >= MAX_NUM_OF_THREADS) return TSL_OUT_OF_SCOPE

cub::Status MultiThreadScheduler::startThread(const ActionThreadId tid, ActionThread& thread, cub::Status& result)
{
   CHECK_TID_SCOPE(tid);

   SWITCH_TO(tid);

   CUB_ASSERT_SUCC_CALL(threads[tid].start(thread, *this));
   doneCheck(tid);

   result = threads[tid].getWorkingStatus();

   return TSL_SUCCESS;
}

cub::Status MultiThreadScheduler::stopThread(const ActionThreadId tid, const cub::Status cause)
{
   CHECK_TID_SCOPE(tid);

   SWITCH_TO(tid);

   cub::Status status = threads[tid].stop(*this, cause);
   if(status != TSL_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }

   return TSL_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::doKillThread(const ActionThreadId tid, const cub::Status cause)
{
   SWITCH_TO(tid);

   if(threads[tid].kill(*this, cause) != TSL_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }
}

//////////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::killThread(const ActionThreadId tid, const cub::Status cause)
{
   CHECK_TID_SCOPE(tid);

   if(current == tid)
   {
      return TSL_INVALID_DATA;
   }

   doKillThread(tid, cause);

   return TSL_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::joinThread(const ActionThreadId tid, cub::Status& result) const
{
   CHECK_TID_SCOPE(tid);

   if(tid == current)
   {
      return TSL_INVALID_DATA;
   }

   result = threads[tid].getWorkingStatus();

   return TSL_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::doStop(const cub::Status cause)
{
   if (stopping)
   {
      return;
   }

   FOREACH_THREAD(tid)
   {
      (void) stopThread(tid, cause);
   }

   stopping = true;
}

/////////////////////////////////////////////////////////////////
ActionStatus MultiThreadScheduler::getMainThreadStatus() const
{
   return threads[MAIN_TID].getWorkingStatus();
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::finalProcess(ActionStatus status)
{
   if(status == TSL_UNKNOWN_EVENT)
   {
      return status;
   }

   if (ActionStatus(getStatus()).isFailed())
   {
      doStop(getStatus());
   }

   if (!getMainThreadStatus().isWorking())
   {
      kill(getStatus());
      return getMainThreadStatus();
   }

   return TSL_CONTINUE;
}

/////////////////////////////////////////////////////////////////
void MultiThreadScheduler::handleEventOnThread(const ActionThreadId tid, const ev::Event& event)
{
   SWITCH_TO(tid);

   cub::Status status = threads[tid].handleEvent(*this, event);
   if(status != TSL_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }
}

/////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::doHandleEvent(const ev::Event& event)
{
   FOREACH_THREAD(tid)
   {
      handleEventOnThread(tid, event);
      if(event.isConsumed())
      {
         return TSL_SUCCESS;
      }
   }

   return TSL_UNKNOWN_EVENT;
}

//////////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::startMainThread(ActionThread& thread)
{
   cub::Status result = TSL_SUCCESS;

   return finalProcess(startThread(MAIN_TID, thread, result));
}

//////////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::handleEvent(const ev::Event& event)
{
   return finalProcess(doHandleEvent(event));
}

//////////////////////////////////////////////////////////////////////
cub::Status MultiThreadScheduler::stop(const cub::Status cause)
{
   doStop(cause);
   return finalProcess(TSL_SUCCESS);
}

//////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::kill(const cub::Status cause)
{
   FOREACH_THREAD(tid)
   {
      doKillThread(tid, cause);
   }
}

//////////////////////////////////////////////////////////////////////
bool MultiThreadScheduler::isWorking() const
{
   return threads[MAIN_TID].getWorkingStatus() == TSL_CONTINUE;
}

TSL_NS_END


