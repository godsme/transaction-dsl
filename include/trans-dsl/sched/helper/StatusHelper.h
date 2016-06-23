/*
 * StatusHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef STATUSHELPER_H_
#define STATUSHELPER_H_

#include <trans-dsl/sched/helper/SwitchCaseHelper.h>
#include <trans-dsl/sched/concept/TransactionInfo.h>

TSL_NS_BEGIN

namespace details
{
   struct AnyFail
   {
      bool operator()(const TransactionInfo& info)
      { return ActionStatus(info.getStatus()).isFailed(); }
   };

   template <cub::Status EXPECTED_STATUS>
   struct IsStatus
   {
      bool operator()(const TransactionInfo& info)
      { return info.getStatus() == EXPECTED_STATUS; }
   };

   template <cub::Status EXCEPT_FAILURE>
   struct FailedExcept
   {
      bool operator()(const TransactionInfo& info)
      { return AnyFail()(info) && info.getStatus() != EXCEPT_FAILURE; }
   };

   struct Whatever
   {
      bool operator()(const TransactionInfo&)
      { return true; }
   };
}

TSL_NS_END

///////////////////////////////////////////////////////////////////////////////////
#define __is_status(status)            TSL_NS::details::IsStatus<status>
#define __is_failed_except(status)     TSL_NS::details::FailedExcept<status>

#define __otherwise(...)               __case(TSL_NS::details::Whatever, __VA_ARGS__)

/////////////////////////////////////////////////////////////////////////
#define __on_fail(action)              __optional(TSL_NS::details::AnyFail, action)
#define __on_succ(action)              __optional(__is_status(TSL_SUCCESS), action)

#define __on_status(status, ...)       __optional(__is_status(status), __VA_ARGS__)
#define __on_fail_except(failure, ...) __optional(__is_failed_except(failure), __VA_ARGS__)

#endif /* STATUSHELPER_H_ */
