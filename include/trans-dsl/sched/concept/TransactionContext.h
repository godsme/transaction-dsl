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

#include <trans-dsl/tsl.h>
#include <cub/dci/Role.h>
#include <cub/base/Status.h>
#include <cub/dci/Unknown.h>

TSL_NS_BEGIN

struct TransactionInfo;
struct TransactionListener;
struct TransactionMode;

struct TransactionContext : com::Unknown
{
   HAS_ROLE(TransactionInfo);
   HAS_ROLE(TransactionListener);
   HAS_ROLE(TransactionMode);
};

TSL_NS_END

#endif /* TRANSACTIONCONTEXT_H_ */
