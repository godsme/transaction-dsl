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

#include <trans-dsl/sched/concept/TransactionMode.h>

TSL_NS_BEGIN

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

TSL_NS_END

#endif /* SIMPLETRANSACTIONMODE_H_ */
