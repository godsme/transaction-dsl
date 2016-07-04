#include <trans-dsl/ext/signal/impl/AbstractTransSignalScheduler.h>
#include <cub/base/Assertions.h>

TSL_NS_BEGIN

using namespace cub;

//////////////////////////////////////////////////////////////////////////
AbstractTransSignalScheduler::AbstractTransSignalScheduler() : signalBitmap(0)
{
}

//////////////////////////////////////////////////////////////////////////
#define BITMASK(signal) (1 << signal)

//////////////////////////////////////////////////////////////////////////
Status AbstractTransSignalScheduler::broadcast(const TransSignalId id)
{
    CUB_ASSERT_TRUE(id <= sizeof(signalBitmap) * 8);

    signalBitmap |= BITMASK(id);

    return CUB_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
TransSignalId AbstractTransSignalScheduler::doFetchSignal()
{
    for(U8 i=0; i < sizeof(TransSignalId) * 8; i++)
    {
        if(signalBitmap & (U32)(1<<i))
        {
            signalBitmap &= ~(U32)(1<<i);
            return i;
        }
    }

    return 0xFF;
}

TSL_NS_END
