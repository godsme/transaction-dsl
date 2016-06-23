include $(HOME)/project/cpp/trans-dsl/shared/ut.mk

test-filter=#-f "safe?mode:*stop*"
tags=-t "throw > seq"

extra-srcs = sched/action/Procedure.cc \
             sched/action/Finally.cc \
             sched/action/NilFinalAction.cc \
             sched/action/LinkedSchedAction.cc \
             sched/action/SchedSequentialAction.cc \
             sched/action/SchedThrowAction.cc \
             sched/action/SchedActionAdapter.cc \
             sched/action/SchedVoidAction.cc \
             sched/action/SchedWaitAction.cc \
             sched/action/SchedPeekAction.cc \
             sched/action/SchedSwitchCaseAction.cc \
             sched/action/SchedConcurrentAction.cc \
             sched/action/SchedLoopAction.cc \
             sched/action/SchedSafeAction.cc \
             sched/action/SchedSafeModeAction.cc \
             sched/action/SchedWithIdAction.cc \
             sched/action/ActionThread.cc \
             sched/action/SchedTimerProtAction.cc \
             sched/trans/SimpleRuntimeContextInfo.cc \
             sched/trans/SimpleTransactionInfo.cc \
             sched/trans/SimpleTransactionMode.cc \
             sched/trans/SchedTransaction.cc \
             sched/trans/BaseTransactionScheduler.cc \
             sched/trans/SimpleTransactionScheduler.cc \
             sched/trans/SimpleTransactionContext.cc \
             sched/trans/TransactionListenerProxy.cc \
             sched/trans/TransMutexSchedulerAdapter.cc \
             action/SimpleAsyncAction.cc \
             action/SyncActionAdapter.cc \
             utils/ActionStatus.cc  \
             utils/RelativeTimer.cc  \
             utils/RuntimeContextAutoSwitch.cc \
             utils/SimpleRuntimeContext.cc \
             utils/AdaptedTimerInfo.cc  \
             utils/StopCause.cc  \
             utils/EventHandlerRegistry.cc  \
             sched/port/PlatformSpecifiedRelativeTimer.cc  \
             ext/mutex/action/SchedLockAction.cc  \
             ext/mutex/impl/AbstractTransMutexScheduler.cc 
             

include $(HOME)/project/cpp/trans-dsl/shared/rules.mk
