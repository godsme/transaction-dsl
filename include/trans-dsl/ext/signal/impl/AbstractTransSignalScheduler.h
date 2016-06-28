#ifndef HDB63EDCC_81C9_4912_8D36_8FC159BC5AC5
#define HDB63EDCC_81C9_4912_8D36_8FC159BC5AC5

#include <cub/base/Status.h>
#include <trans-dsl/ext/signal/concept/TransSignalScheduler.h>

TSL_NS_BEGIN

struct AbstractTransSignalScheduler
    : TransSignalScheduler
{
    AbstractTransSignalScheduler();

    TransSignalId fetchSignal()
    {
        if(signalBitmap == 0) return 0xFF;

        return doFetchSignal();
    }

private:
    OVERRIDE(cub::Status broadcast(const TransSignalId));
    TransSignalId doFetchSignal();

protected:
    cub::U32 signalBitmap;
};

TSL_NS_END

#endif /* HDB63EDCC_81C9_4912_8D36_8FC159BC5AC5 */
