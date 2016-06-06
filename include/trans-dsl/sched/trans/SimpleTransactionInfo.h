/*
 * SimpleTransactionInfo.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTIONINFO_H_
#define SIMPLETRANSACTIONINFO_H_

#include "trans-dsl/sched/concept/TransactionInfo.h"

struct RuntimeContextInfo;

struct SimpleTransactionInfo : TransactionInfo
{
   explicit SimpleTransactionInfo(InstanceId iid = 0);

   OVERRIDE(InstanceId getInstanceId() const);
   OVERRIDE(Status getStatus() const);
   OVERRIDE(Unknown* getUserContext() const);

   void updateUserContext(Unknown*);
   void updateInstanceId(InstanceId iid);

private:
   InstanceId iid;
   Unknown*   userContext;

private:
   USE_ROLE(RuntimeContextInfo);
};

#endif /* SIMPLETRANSACTIONINFO_H_ */
