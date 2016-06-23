#include <testngpp/testngpp.hpp>
#include <trans-dsl/TransactionDSL.h>
#include "event/impl/SimpleEventInfo.h"
#include "event/concept/Event.h"
#include "trans-dsl/ext/mutex/impl/AbstractTransMutexScheduler.h"
#include "trans-dsl/ext/mutex/impl/TransMutexAvailNotifier.h"
#include "trans-dsl/ext/mutex/def/TransMutexAvailMsg.h"
#include <event/impl/ConsecutiveEventInfo.h>

using namespace ev;
using namespace tsl;
using namespace cub;

namespace cub
{
  extern void log_error(const char* file, unsigned int line, const char* fmt, ...)
  {
  }
}

#define EVENT(n) SimpleEventInfo(n)

struct SimpleMutexAvailNotifier
   : TransMutexAvailNotifier
{
   void notifyMutexAvail(TransMutexId mutex)
   {
      mutexAvailSignal |= (1 << mutex);
   }

   bool mutexReleased(TransMutexId mutex) const
   {
      return mutexAvailSignal & (1 << mutex);
   }

private:
   U8 mutexAvailSignal;
};

#define MUTEX_EVENT(n) ConsecutiveEventInfo(EV_MUTEX_UNLOCK, TransMutexAvailMsg(n))

struct MyScheduler
   : SimpleMutexAvailNotifier
   , AbstractTransMutexScheduler
{
      IMPL_ROLE(TransMutexAvailNotifier);
};

FIXTURE(Mutex)
{
   __mt_transaction
   ( __sequential
       ( __wait(1)
       , __lock(1, __wait(2))
       , __wait(3))
   ) trans1;

   __mt_transaction
   ( __sequential
       ( __wait(4)
       , __lock(1, __wait(5))
       , __wait(6))
   ) trans2;

   MyScheduler sched;

   SETUP()
   {
      trans1.updateMutexScheduler(sched);
      trans2.updateMutexScheduler(sched);

      ASSERT_EQ(TSL_CONTINUE, trans1.start());
      ASSERT_EQ(TSL_CONTINUE, trans2.start());
   }

   // @test(id="trans-1-lock")
   TEST("recv event-1, event-4")
   {
      ASSERT_EQ(TSL_CONTINUE, trans1.handleEvent(EVENT(1)));
      ASSERT_EQ(TSL_CONTINUE, trans2.handleEvent(EVENT(4)));
   }

   // @test(depends="trans-1-lock")
   TEST("after trans1 gets the lock, trans2 should refuse event-5")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans2.handleEvent(EVENT(5)));
   }

   // @test(id="trans-1-unlock", depends="trans-1-lock")
   TEST("after trans1 gets the lock, trans1 should accept event-2")
   {
      ASSERT_EQ(TSL_CONTINUE, trans1.handleEvent(EVENT(2)));
   }

   // @test(depends="trans-1-unlock")
   TEST("after trans1 release the lock, trans2 should accept event-5")
   {
      ASSERT_TRUE(sched.mutexReleased(1));

      ASSERT_EQ(TSL_CONTINUE, trans2.handleEvent(MUTEX_EVENT(1)));
      ASSERT_EQ(TSL_CONTINUE, trans2.handleEvent(EVENT(5)));
   }

   // @test(depends="trans-1-unlock")
   TEST("after trans1 release the lock, trans1 should not accept mutex event")
   {
      ASSERT_EQ(TSL_UNKNOWN_EVENT, trans1.handleEvent(MUTEX_EVENT(1)));
   }
};


