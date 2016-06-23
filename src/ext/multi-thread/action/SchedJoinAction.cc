/*
 * SchedJoinAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include <trans-dsl/ext/multi-thread/action/SchedJoinAction.h>
#include <trans-dsl/ext/multi-thread/concept/MultiThreadContext.h>
#include <trans-dsl/ext/multi-thread/def/ThreadDoneMsg.h>
#include <trans-dsl/sched/concept/TransactionContext.h>
#include <trans-dsl/utils/ActionStatus.h>

#include <cub/base/Assertions.h>
#include <cub/dci/Unknown.h>
#include <event/concept/Event.h>

TSL_NS_BEGIN

////////////////////////////////////////////////////////////
SchedJoinAction::SchedJoinAction() :
                  joinPointBitmap(0)
{
}

////////////////////////////////////////////////////////////
#define BITMASK(n) (1 << n)

cub::Status SchedJoinAction::reschedule()
{
   return joinPointBitmap > 0 ? TSL_CONTINUE : TSL_SUCCESS;
}

////////////////////////////////////////////////////////////
bool SchedJoinAction::isWaiting(const ActionThreadId threadId) const
{
   return joinPointBitmap & ((HostType) BITMASK(threadId));
}

////////////////////////////////////////////////////////////
void SchedJoinAction::addThread(const ActionThreadId threadId)
{
   joinPointBitmap |= ((HostType) BITMASK(threadId));
}

////////////////////////////////////////////////////////////
void SchedJoinAction::threadDone(const ActionThreadId threadId)
{
   joinPointBitmap &= ~((HostType) BITMASK(threadId));
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::addJoinThread(const ActionThreadId threadId)
{
   if (threadId >= sizeof(HostType) * 8)
   {
      return TSL_OUT_OF_SCOPE;
   }

   addThread(threadId);

   return TSL_SUCCESS;
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::onThreadDone(const ActionThreadId tid, const cub::Status result)
{
   if (!isWaiting(tid))
   {
      return TSL_UNKNOWN_EVENT;
   }

   if(ActionStatus(result).isFailed())
   {
      return result;
   }

   threadDone(tid);

   return reschedule();
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::handleEvent(TransactionContext&, const ev::Event& event)
{
   if (!event.matches(EV_ACTION_THREAD_DONE))
   {
      return TSL_UNKNOWN_EVENT;
   }

   const ThreadDoneMsg* msg = (const ThreadDoneMsg*) event.getMsg();
   CUB_ASSERT_VALID_PTR(msg);

   return onThreadDone(msg->who, msg->result);
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::join(const ActionThreadId threadId,
         TransactionContext& context)
{
   MultiThreadContext* mt = com::unknown_cast<MultiThreadContext>(&context);
   CUB_ASSERT_VALID_PTR(mt);

   cub::Status result = TSL_SUCCESS;
   CUB_ASSERT_SUCC_CALL(mt->joinThread(threadId, result));
   if (!ActionStatus(result).isWorking())
   {
      threadDone(threadId);
      return result;
   }

   return TSL_SUCCESS;
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::exec(TransactionContext& context)
{
   ActionThreadId tid = 0;
   for (HostType bitmap = joinPointBitmap; bitmap > 0; bitmap >>= 1, ++tid)
   {
      if (bitmap & 0x1)
      {
         CUB_ASSERT_SUCC_CALL(join(tid, context));
      }
   }

   return reschedule();
}

////////////////////////////////////////////////////////////
cub::Status SchedJoinAction::stop(TransactionContext& context, const cub::Status cause)
{
   kill(context, cause);

   return cause;
}

////////////////////////////////////////////////////////////
void SchedJoinAction::kill(TransactionContext&, const cub::Status)
{
   joinPointBitmap = 0;
}

TSL_NS_END


