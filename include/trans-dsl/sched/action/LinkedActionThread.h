/*
 * LinkedActionThread.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDACTIONTHREAD_H_
#define LINKEDACTIONTHREAD_H_

#include "trans-dsl/sched/action/ActionThread.h"
#include <base/utils/ListElem.h>

struct LinkedActionThread
         : ActionThread
         , ListElem<LinkedActionThread>
{
private:
   USE_ROLE(SchedAction);
};

#endif /* LINKEDACTIONTHREAD_H_ */
