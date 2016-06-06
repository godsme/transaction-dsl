/*
 * SimpleTransactionMode.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTIONMODE_H_
#define SIMPLETRANSACTIONMODE_H_

#include "trans-dsl/sched/concept/TransactionMode.h"

struct SimpleTransactionMode : TransactionMode
{
   SimpleTransactionMode();

   OVERRIDE(void enterSafeMode());
   OVERRIDE(void leaveSafeMode());

protected:
   bool inSafeMode() const;

private:
   bool safeMode;
};

#endif /* SIMPLETRANSACTIONMODE_H_ */
