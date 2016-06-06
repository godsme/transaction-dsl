/*
 * ActionThreadId.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONTHREADID_H_
#define ACTIONTHREADID_H_

typedef unsigned char ActionThreadId;

const ActionThreadId MAIN_TID       = 0;
const ActionThreadId NIL_TID        = 0xFF;

#endif /* ACTIONTHREADID_H_ */
