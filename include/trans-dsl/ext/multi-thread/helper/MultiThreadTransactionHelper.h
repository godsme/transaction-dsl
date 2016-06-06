/*
 * MultiThreadTransactionHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADTRANSACTIONHELPER_H_
#define MULTITHREADTRANSACTIONHELPER_H_

#include "trans-dsl/ext/multi-thread/trans/MultiThreadTransaction.h"
#include "trans-dsl/ext/multi-thread/helper/ThreadHelper.h"
#include "trans-dsl/sched/helper/ProcedureHelper.h"

namespace details
{
   template<typename T_ACTION>
   struct MULTI_THREAD_TRANSACTION__: MultiThreadTransaction
   {
      explicit MULTI_THREAD_TRANSACTION__(const InstanceId iid = 0)
          : MultiThreadTransaction(iid) {}

   private:
      typedef THREAD__<T_ACTION> Thread;
      IMPL_ROLE_WITH_VAR(ActionThread, Thread);
   };
}

///////////////////////////////////////////////////////////////////////
#define __mt_transaction(...) \
     details::MULTI_THREAD_TRANSACTION__< details::PROCEDURE__< __VA_ARGS__ > >

#define __def_mt_transaction(...) \
     typedef __mt_transaction(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define __prot_mt_transaction(...) \
     details::MULTI_THREAD_TRANSACTION__< details::PROTECTED_PROC__<__VA_ARGS__ > >

#define __def_prot_mt_transaction(...) \
     typedef __prot_mt_transaction(__VA_ARGS__)

#endif /* MULTITHREADTRANSACTIONHELPER_H_ */
