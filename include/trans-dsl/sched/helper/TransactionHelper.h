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

///////////////////////////////////////////////////////////////////////
#define __transaction(...) \
     details::TRANSACTION__< details::PROCEDURE__<__VA_ARGS__ > >

#define __def_transaction(...) \
     typedef __transaction(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////
#define __prot_transaction(...) \
     details::TRANSACTION__< details::PROTECTED_PROC__<__VA_ARGS__ > >

#define __def_prot_transaction(...) \
     typedef __prot_transaction(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////

#endif /* TRANSACTIONHELPER_H_ */
