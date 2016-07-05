#ifndef H41037034_2B25_4F59_BF43_5B607BAA5DD0
#define H41037034_2B25_4F59_BF43_5B607BAA5DD0

#include <trans-dsl/sched/trans/SchedTransaction.h>
#include <cub/dci/Unknown.h>
#include <cub/log/log.h>
#include <cub/mem/Placement.h>

TSL_NS_BEGIN

///////////////////////////////////////////////////////////////////
template <typename TIMER_INFO, typename TRANS, typename CONTEXT, typename LISTENER>
struct GenericTransaction : TRANS
{
    GenericTransaction(const InstanceId iid) : iid(iid)
    {
        context.init();
    }

    virtual ~GenericTransaction() {}

    OVERRIDE(cub::Status start())
    {
        TRANS::updateInstanceId(iid);
        TRANS::updateTimerInfo(TIMER_INFO::getInstance());
        TRANS::updateUserContext(context.getObject());
        TRANS::updateTransactionListener(listener);

        return TRANS::start();
    }

    com::Unknown* getUserContext() const
    {
        return context.getObject();
    }

private:
    InstanceId iid;

private:
    TRANS    trans;
    cub::DefaultPlacement<CONTEXT>  context;
    LISTENER listener;
};

TSL_NS_END

#endif /* H41037034_2B25_4F59_BF43_5B607BAA5DD0 */
