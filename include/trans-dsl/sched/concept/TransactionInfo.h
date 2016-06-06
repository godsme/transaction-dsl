/*
 * TransactionInfo.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONINFO_H_
#define TRANSACTIONINFO_H_

#include <trans-dsl/sched/concept/InstanceId.h>
#include <base/Status.h>
#include <base/dci/Role.h>
#include <base/dci/Unknown.h>

DEFINE_ROLE(TransactionInfo)
{
   ABSTRACT(InstanceId getInstanceId() const);
   ABSTRACT(Status getStatus() const);
   ABSTRACT(Unknown* getUserContext() const);

   template <typename ROLE>
   ROLE* toRole() const
   {
      return unknown_cast<ROLE>(getUserContext());
   }
};

#endif /* TRANSACTIONINFO_H_ */
