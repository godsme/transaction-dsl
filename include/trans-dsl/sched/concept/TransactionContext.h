/*
 * TransactionContext.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONCONTEXT_H_
#define TRANSACTIONCONTEXT_H_

#include <base/dci/Role.h>
#include <base/Status.h>
#include <base/dci/Unknown.h>

struct TransactionInfo;
struct TransactionListener;
struct TransactionMode;

struct TransactionContext : Unknown
{
   HAS_ROLE(TransactionInfo);
   HAS_ROLE(TransactionListener);
   HAS_ROLE(TransactionMode);
};

#endif /* TRANSACTIONCONTEXT_H_ */
