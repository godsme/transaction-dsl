/*
 * ActionPath.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONPATH_H_
#define ACTIONPATH_H_

#include <base/dci/ListBasedRole.h>
#include <base/Status.h>

struct TransactionInfo;
struct SchedAction;

DEFINE_LIST_BASED_ROLE(ActionPath)
{
   ABSTRACT(bool shouldExecute(const TransactionInfo&));
   ABSTRACT(SchedAction& getAction());
};

#endif /* ACTIONPATH_H_ */
