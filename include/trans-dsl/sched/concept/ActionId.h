/*
 * ActionId.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONID_H_
#define ACTIONID_H_

#include <trans-dsl/tsl.h>

TSL_NS_BEGIN

typedef unsigned short ActionId;

const ActionId NIL_ACTION_ID = 0xFFFF;
TSL_NS_END

#endif /* ACTIONID_H_ */
