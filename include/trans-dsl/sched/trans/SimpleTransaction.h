/*
 * SimpleTransaction.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTION_H_
#define SIMPLETRANSACTION_H_

#include "trans-dsl/sched/trans/SchedulerBasedTransaction.h"
#include "trans-dsl/sched/trans/SimpleTransactionScheduler.h"

typedef SchedulerBasedTransaction<SimpleTransactionScheduler> SimpleTransaction;

#endif /* SIMPLETRANSACTION_H_ */
