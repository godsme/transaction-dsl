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

#include <base/dci/Role.h>

DEFINE_ROLE(TransactionMode)
{
   ABSTRACT(void enterSafeMode());
   ABSTRACT(void leaveSafeMode());
};

#endif /* TRANSACTIONMODE_H_ */
