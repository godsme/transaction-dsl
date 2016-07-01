#ifndef H02B854A2_C825_42C1_AE12_68A7388A80D2
#define H02B854A2_C825_42C1_AE12_68A7388A80D2

#include <trans-dsl/sched/concept/Transaction.h>

TSL_NS_BEGIN

struct TransMutexScheduler;
struct TransSignalScheduler;

struct LockableTransaction : Transaction
{
    ABSTRACT(void updateMutexScheduler(TransMutexScheduler&));
    ABSTRACT(void updateSignalScheduler(TransSignalScheduler&));

    ABSTRACT(void init(const InstanceId&));
    ABSTRACT(void destroy());
};

TSL_NS_END

#endif /* H02B854A2_C825_42C1_AE12_68A7388A80D2 */
