//
// Created by Darwin Yuan on 2020/6/17.
//

#include <nanobench/nanobench.h>
#include <trans-dsl/TransactionDSL.h>
#include <event/impl/SimpleEventInfo.h>
#include <event/impl/ConsecutiveEventInfo.h>
#include "trans-dsl/utils/SimpleRuntimeContext.h"
#include "trans-dsl/sched/trans/SimpleTransactionContext.h"
#include <iostream>

using namespace tsl;

struct MyContext : private SimpleRuntimeContext, SimpleTransactionContext
{
   MyContext() : SimpleTransactionContext((RuntimeContext&)*this)
   {
   }
};

MyContext context;

#define SIMPLE_EVENT(n) \
const EV_NS::SimpleEventInfo ev_## n{n}

SIMPLE_EVENT(1);
SIMPLE_EVENT(2);
SIMPLE_EVENT(3);
SIMPLE_EVENT(4);
SIMPLE_EVENT(5);
SIMPLE_EVENT(6);
SIMPLE_EVENT(7);
SIMPLE_EVENT(8);
SIMPLE_EVENT(9);


void func() {
   __procedure
   ( __sequential
        ( __wait(1)
        , __wait(2)
        , __wait(3)
        , __wait(4)
        , __wait(5)
        , __wait(6)),
     __finally( __sequential(__wait(7), __wait(8), __wait(9)))
   ) proc;

   proc.exec(context);
   proc.handleEvent(context, ev_1);
   proc.handleEvent(context, ev_2);
   proc.handleEvent(context, ev_3);
   proc.handleEvent(context, ev_4);
   proc.handleEvent(context, ev_5);
   proc.handleEvent(context, ev_6);
   proc.handleEvent(context, ev_7);
   proc.handleEvent(context, ev_8);
   proc.handleEvent(context, ev_9);
}

const EV_NS::EventId EV_ID_1 = 1000;
const EV_NS::EventId EV_ID_2 = 2000;
const EV_NS::EventId EV_ID_4 = 4000;
struct Msg1 {
   int a = 0;
   int b = 0;
};

struct Msg2 {
   int a = 0;
};

struct Msg4 {
   int a = 0;
};

DEF_SIMPLE_REQ_ACTION(AsyncAction1, EV_ID_1, Msg1);
IMPL_SIMPLE_REQ_ACTION(AsyncAction1, Msg1) {
   return TSL_SUCCESS;
}

DEF_SIMPLE_REQ_ACTION(AsyncAction2, EV_ID_2, Msg2);
IMPL_SIMPLE_REQ_ACTION(AsyncAction2, Msg2) {
   return TSL_SUCCESS;
}

DEF_SIMPLE_REQ_ACTION(AsyncAction4, EV_ID_4, Msg4);
IMPL_SIMPLE_REQ_ACTION(AsyncAction4, Msg4) {
   return TSL_SUCCESS;
}

using ProcedureAction1 =
      __procedure(
         __wait(1),
         __finally(__asyn(AsyncAction2)));

using ProcedureAction2 =
      __procedure(
         __wait(2),
         __finally(__asyn(AsyncAction1)));

using ProcedureAction3 =
   __procedure(
      __wait(3),
      __finally(__asyn(AsyncAction4)));

using Concurrent = __concurrent(ProcedureAction1, ProcedureAction2);
using Concurrent1 = __concurrent(ProcedureAction1, ProcedureAction2, ProcedureAction3);

const Msg1 msg1{ 10, 20 };
const EV_NS::ConsecutiveEventInfo eventInfo1{EV_ID_1, msg1};

const Msg2 msg2{ 30 };
const EV_NS::ConsecutiveEventInfo eventInfo2{EV_ID_2, msg2};

const Msg4 msg4{ 30 };
const EV_NS::ConsecutiveEventInfo eventInfo4{EV_ID_4, msg4};

using Proc2 = __procedure
( __sequential
     ( __wait(1)
        , __wait(2)
        , __wait(3)
        , __wait(4)
        , __wait(5)
        , __wait(6)
        , Concurrent1),
  __finally(__sequential(__wait(7), __wait(8), __wait(9)))
);
void func1() {
   Concurrent action;

   assert(TSL_CONTINUE == action.exec(context));
   assert(TSL_CONTINUE == action.handleEvent(context, ev_1));
   assert(TSL_CONTINUE == action.handleEvent(context, ev_2));
   assert(TSL_CONTINUE == action.handleEvent(context, eventInfo1));
   assert(TSL_SUCCESS  == action.handleEvent(context, eventInfo2));
}

void func2() {
   Concurrent1 action;

   assert(TSL_CONTINUE == action.exec(context));
   assert(TSL_CONTINUE == action.handleEvent(context, ev_1));
   assert(TSL_CONTINUE == action.handleEvent(context, ev_2));
   assert(TSL_CONTINUE == action.handleEvent(context, ev_3));
   assert(TSL_CONTINUE == action.handleEvent(context, eventInfo1));
   assert(TSL_CONTINUE == action.handleEvent(context, eventInfo4));
   assert(TSL_SUCCESS  == action.handleEvent(context, eventInfo2));
}

void func3() {
   Proc2 proc;

   assert(TSL_CONTINUE == proc.exec(context));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_1));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_2));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_3));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_4));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_5));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_6));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_1));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_2));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_3));
   assert(TSL_CONTINUE == proc.handleEvent(context, eventInfo1));
   assert(TSL_CONTINUE == proc.handleEvent(context, eventInfo4));
   assert(TSL_CONTINUE == proc.handleEvent(context, eventInfo2));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_7));
   assert(TSL_CONTINUE == proc.handleEvent(context, ev_8));
   assert(TSL_SUCCESS == proc.handleEvent(context, ev_9));
}

int main() {
   std::cout << sizeof(Proc2) << std::endl;
   ankerl::nanobench::Bench().epochs(1000).run("run-procedure", [&] {
      func3();
   });

   return 0;
}
