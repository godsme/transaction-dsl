/*
 * SyncAction.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SYNCACTION_H_
#define SYNCACTION_H_

#include "base/dci/Role.h"
#include "base/Status.h"

struct TransactionInfo;

DEFINE_ROLE(SyncAction)
{
   ABSTRACT(Status exec(const TransactionInfo&));
};

#endif /* SYNCACTION_H_ */
