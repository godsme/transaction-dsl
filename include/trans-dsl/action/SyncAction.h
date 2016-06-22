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

#include <trans-dsl/tsl.h>

#include <cub/dci/Role.h>
#include <cub/base/Status.h>

TSL_NS_BEGIN

struct TransactionInfo;

DEFINE_ROLE(SyncAction)
{
	ABSTRACT(cub::Status exec(const TransactionInfo&));
};

TSL_NS_END

#endif /* SYNCACTION_H_ */
