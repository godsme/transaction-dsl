/*
 * SchedJoinAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "trans-dsl/ext/multi-thread/action/SchedJoinAction.h"
#include "base/utils/Assertions.h"
#include "trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "base/dci/Unknown.h"
#include "event/concept/Event.h"
#include "trans-dsl/ext/multi-thread/def/ThreadDoneMsg.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "trans-dsl/utils/ActionStatus.h"

////////////////////////////////////////////////////////////
SchedJoinAction::SchedJoinAction() :
                  joinPointBitmap(0)
{
}

////////////////////////////////////////////////////////////
#define BITMASK(n) (1 << n)

Status SchedJoinAction::reschedule()
{
   return joinPointBitmap > 0 ? CONTINUE : SUCCESS;
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
Status SchedJoinAction::addJoinThread(const ActionThreadId threadId)
{
   if (threadId >= sizeof(HostType) * 8)
   {
      return OUT_OF_SCOPE;
   }

   addThread(threadId);

   return SUCCESS;
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::onThreadDone(const ActionThreadId tid, const Status result)
{
   if (!isWaiting(tid))
   {
      return UNKNOWN_EVENT;
   }

   if(ActionStatus(result).isFailed())
   {
      return result;
   }

   threadDone(tid);

   return reschedule();
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::handleEvent(TransactionContext&, const Event& event)
{
   if (!event.matches(EV_ACTION_THREAD_DONE))
   {
      return UNKNOWN_EVENT;
   }

   const ThreadDoneMsg* msg = (const ThreadDoneMsg*) event.getMsg();
   DCM_ASSERT_VALID_PTR(msg);

   return onThreadDone(msg->who, msg->result);
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::join(const ActionThreadId threadId,
         TransactionContext& context)
{
   MultiThreadContext* mt = unknown_cast<MultiThreadContext>(&context);
   DCM_ASSERT_VALID_PTR(mt);

   Status result = SUCCESS;
   DCM_ASSERT_SUCC_CALL(mt->joinThread(threadId, result));
   if (!ActionStatus(result).isWorking())
   {
      threadDone(threadId);
      return result;
   }

   return SUCCESS;
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::exec(TransactionContext& context)
{
   ActionThreadId tid = 0;
   for (HostType bitmap = joinPointBitmap; bitmap > 0; bitmap >>= 1, ++tid)
   {
      if (bitmap & 0x1)
      {
         DCM_ASSERT_SUCC_CALL(join(tid, context));
      }
   }

   return reschedule();
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::stop(TransactionContext& context, const Status cause)
{
   kill(context, cause);

   return cause;
}

////////////////////////////////////////////////////////////
void SchedJoinAction::kill(TransactionContext&, const Status)
{
   joinPointBitmap = 0;
}


