/*
 * TransactionHelper.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONHELPER_H_
#define TRANSACTIONHELPER_H_

#include "trans-dsl/sched/trans/SimpleTransaction.h"
#include "trans-dsl/sched/helper/ProcedureHelper.h"
#include "trans-dsl/ext/multi-thread/helper/ThreadHelper.h"

TSL_NS_BEGIN

namespace details
{
   template <typename T_ACTION>
   struct TRANSACTION__ : SimpleTransaction
   {
      TRANSACTION__(InstanceId iid = 0) : SimpleTransaction(iid)
      {}

   private:
      typedef THREAD__<T_ACTION> Thread;
      IMPL_ROLE_WITH_VAR(ActionThread, Thread);
   };
};

TSL_NS_END

///////////////////////////////////////////////////////////////////////
#define __transaction(...) \
     TSL_NS::details::TRANSACTION__< TSL_NS::details::PROCEDURE__<__VA_ARGS__ > >

#define __def_transaction(...) \
     typedef __transaction(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////
#define __prot_transaction(...) \
    TSL_NS::details::TRANSACTION__< TSL_NS::details::PROTECTED_PROC__<__VA_ARGS__ > >

#define __def_prot_transaction(...) \
     typedef __prot_transaction(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////

#endif /* TRANSACTIONHELPER_H_ */
