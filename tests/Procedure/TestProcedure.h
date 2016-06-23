

#include <testngpp/testngpp.hpp>
#include "trans-dsl/TransactionDSL.h"
#include "trans-dsl/sched/concept/TransactionContext.h"
#include "event/impl/SimpleEventInfo.h"
#include "event/concept/Event.h"
#include "trans-dsl/utils/SimpleRuntimeContext.h"
#include "trans-dsl/sched/trans/SimpleTransactionContext.h"

using namespace cub;
using namespace tsl;
using namespace ev;

namespace cub
{
  extern void log_error(const char* file, unsigned int line, const char* fmt, ...)
  {
  }
}

enum : Status
{
    ERROR1 = failStatus(200),
    ERROR2,
    ERROR3,
    ERROR4
};


struct MyContext : private SimpleRuntimeContext, SimpleTransactionContext
{
   MyContext() : SimpleTransactionContext((RuntimeContext&)*this)
   {
   }
};

FIXTURE(proc1)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   , __finally
       ( __wait(3))
   ) proc;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR1));
      ASSERT_EQ(ERROR1, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(proc2)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   , __finally
       ( __wait(3))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(ERROR1, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR2));
      ASSERT_EQ(ERROR2, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(proc3)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   , __finally
       ( __sequential
           (__wait(3)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR1));
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(proc4)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   , __finally
       ( __sequential
           (__wait(3)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(ERROR3, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(proc5)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(ERROR1, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(ERROR2, proc.stop(context, ERROR2));
      ASSERT_EQ(ERROR2, getStatus());
   }
};

FIXTURE(proc6)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(ERROR2, proc.stop(context, ERROR2));
      ASSERT_EQ(ERROR2, getStatus());
   }
};

FIXTURE(proc7)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __procedure
           ( __sequential
               ( __wait(2)
               , __throw(ERROR1))
           , __finally
               (__sequential
                  ( __wait(3)
                  , __throw(ERROR2)))))
   , __finally
       ( __sequential
           (__wait(4)
           , __throw(ERROR3)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(ERROR2, getStatus());

      ASSERT_EQ(ERROR3,   proc.handleEvent(context, SimpleEventInfo(4)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR4));
      ASSERT_EQ(ERROR4, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(ERROR2, getStatus());

      ASSERT_EQ(ERROR3,   proc.handleEvent(context, SimpleEventInfo(4)));
   }
};

FIXTURE(proc8)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __throw(ERROR1))
   , __finally
       ( __sequential
           (__wait(2)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(ERROR1, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(proc9)
{
   __procedure
   (  __wait(1)
   , __finally
       ( __wait(2))
   ) proc;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(proc10)
{
   __procedure
   ( __prot_procedure(__wait(1))
   , __finally
       ( __on_succ(__wait(2)))
   ) proc;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
   }

   TEST("after start, if stopped, should return CONTINUE")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(proc11)
{
   __procedure
   ( __prot_procedure(__wait(1))
   , __finally
       ( __on_fail(__wait(2)))
   ) proc;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
   }

   TEST("after start, if stopped, should return SUCCESS")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.stop(context, ERROR3));
   }
};

FIXTURE(prot_proc1)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   , __finally
       ( __wait(3))
   ) proc;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
   }

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR1));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(prot_proc2)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   , __finally
       ( __wait(3))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR2));
      ASSERT_EQ(TSL_SUCCESS, getStatus());
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(prot_proc3)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   , __finally
       ( __sequential
           (__wait(3)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR1));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};

FIXTURE(prot_proc4)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   , __finally
       ( __sequential
           (__wait(3)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(3)));
   }
};


FIXTURE(prot_proc5)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2)
       , __throw(ERROR1))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(2)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.stop(context, ERROR2));
   }
};

FIXTURE(prot_proc6)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __wait(2))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_SUCCESS, proc.stop(context, ERROR2));
   }
};


FIXTURE(prot_proc7)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __procedure
           ( __sequential
               ( __wait(2)
               , __throw(ERROR1))
           , __finally
               (__sequential
                  ( __wait(3)
                  , __throw(ERROR2)))))
   , __finally
       ( __sequential
           (__wait(4)
           , __throw(ERROR3)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR3, proc.handleEvent(context, SimpleEventInfo(4)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR4));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR3, proc.handleEvent(context, SimpleEventInfo(4)));
   }
};

FIXTURE(prot_proc8)
{
   __prot_procedure
   ( __sequential
       ( __wait(1)
       , __throw(ERROR1))
   , __finally
       ( __sequential
           (__wait(2)
           , __throw(ERROR2)))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(ERROR2, proc.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(prot_proc9)
{
   __procedure
   ( __sequential
       ( __wait(1)
       , __prot_procedure
           ( __sequential
               ( __wait(2)
               , __throw(ERROR1))
           , __finally(__wait(3))))
   , __finally(__wait(4))
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should return correct result")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(4)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(TSL_SUCCESS, getStatus());

      ASSERT_EQ(TSL_SUCCESS, proc.handleEvent(context, SimpleEventInfo(4)));
   }
};

FIXTURE(seq1)
{
   __sequential
   ( __prot_procedure
       ( __sequential
           ( __wait(1)
           , __throw(ERROR1))
       , __finally(__wait(2)))
   , __wait(3)
   ) proc;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, proc.exec(context));
      ASSERT_EQ(TSL_CONTINUE, proc.handleEvent(context, SimpleEventInfo(1)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, proc.stop(context, ERROR3));

      ASSERT_EQ(ERROR3, proc.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(concurrent1)
{
   __concurrent
   ( __prot_procedure
       ( __sequential
           ( __wait(1)
           , __throw(ERROR1))
       , __finally(__wait(2)))
   , __throw(ERROR2)
   ) action;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, action.exec(context));
   }

   TEST("should be able exec")
   {
      ASSERT_EQ(ERROR2, action.handleEvent(context, SimpleEventInfo(2)));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, action.stop(context, ERROR3));

      ASSERT_EQ(ERROR2, action.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(concurrent2)
{
   __concurrent
   ( __procedure
       ( __wait(1)
       , __finally(__throw(ERROR1)))
   , __throw(ERROR2)
   ) action;

   MyContext context;

   TEST("should be able exec")
   {
      ASSERT_EQ(ERROR1, action.exec(context));
   }
};

FIXTURE(concurrent3)
{
   __concurrent
   ( __prot_procedure
       ( __wait(1)
       , __finally
          ( __sequential
              ( __wait(2)
              , __throw(ERROR1))))
   , __throw(ERROR2)
   ) action;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, action.exec(context));
      ASSERT_EQ(ERROR2, getStatus());
   }

   TEST("should be able exec")
   {
      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, action.stop(context, ERROR3));

      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());
   }
};

FIXTURE(concurrent4)
{
   __def(prot_proc) __as_prot_procedure
   ( __wait(1)
   , __finally
       ( __sequential
           ( __wait(2)
           , __throw(ERROR1)))
   );

   __concurrent
   ( __apply(prot_proc)
   , __sequential
       ( __wait(3)
       , __throw(ERROR2))
   ) action;

   MyContext context;

   Status getStatus() const
   {
      return ((TransactionContext&)context).ROLE(TransactionInfo).getStatus();
   }

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, action.exec(context));
      ASSERT_EQ(TSL_SUCCESS, getStatus());
   }

   TEST("should be able exec")
   {
      ASSERT_EQ(TSL_CONTINUE, action.handleEvent(context, SimpleEventInfo(3)));
      ASSERT_EQ(ERROR2, getStatus());

      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, action.stop(context, ERROR3));

      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
      ASSERT_EQ(ERROR1, getStatus());
   }
};

FIXTURE(concurrent5)
{
   __def(prot_proc) __as_prot_procedure
   ( __wait(1)
   , __finally
       ( __on_fail
           ( __sequential
               ( __wait(2)
               , __throw(ERROR1))))
   );

   __concurrent
   ( __apply(prot_proc)
   , __sequential
       ( __wait(3)
       , __throw(ERROR2))
   ) action;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, action.exec(context));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, action.stop(context, ERROR3));

      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
   }
};

FIXTURE(concurrent6)
{
   __def(prot_proc) __as_prot_procedure
   ( __wait(1)
   , __finally
       ( __on_status( ERROR3, __sequential
                                ( __wait(2)
                                , __throw(ERROR1))))
   );

   __concurrent
   ( __apply(prot_proc)
   , __sequential
       ( __wait(3)
       , __throw(ERROR2))
   ) action;

   MyContext context;

   SETUP()
   {
      ASSERT_EQ(TSL_CONTINUE, action.exec(context));
   }

   TEST("should be able to stop")
   {
      ASSERT_EQ(TSL_CONTINUE, action.stop(context, ERROR3));

      ASSERT_EQ(ERROR1, action.handleEvent(context, SimpleEventInfo(2)));
   }
};

