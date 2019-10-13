#ifndef HA466B077_02E9_4409_95A5_4599FE9B2B9A
#define HA466B077_02E9_4409_95A5_4599FE9B2B9A

#include <trans-dsl/tsl.h>
#include <cub/dci/InterfaceDef.h>
#include <cub/dci/Role.h>
#include <trans-dsl/ext/signal/concept/TransSignalId.h>

TSL_NS_BEGIN

UNKNOWN_INTERFACE(TransSignalScheduler, 0x09061329)
{
    ABSTRACT(cub::Status broadcast(const TransSignalId));
};

TSL_NS_END

#endif /* HA466B077_02E9_4409_95A5_4599FE9B2B9A */
