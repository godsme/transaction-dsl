/*
 * TransactionMode.h
 *
 * Created on: Jun 10, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONMODE_H_
#define TRANSACTIONMODE_H_

#include <cub/dci/Role.h>
#include <trans-dsl/tsl.h>

TSL_NS_BEGIN

DEFINE_ROLE(TransactionMode)
{
   ABSTRACT(void enterSafeMode());
   ABSTRACT(void leaveSafeMode());
};

TSL_NS_END

#endif /* TRANSACTIONMODE_H_ */
