/*
 * DeclState.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef DECLSTATE_H_
#define DECLSTATE_H_

#define __DECL_STATE(S) struct S; \
   Status goto##S##State(TransactionContext&, const Status)

#endif /* DECLSTATE_H_ */
