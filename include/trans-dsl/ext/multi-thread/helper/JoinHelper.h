/*
 * JoinHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef JOINHELPER_H_
#define JOINHELPER_H_

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include "trans-dsl/ext/multi-thread/helper/11/Join11.h"
#else
#include "trans-dsl/ext/multi-thread/helper/98/Join98.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////
#define __join(...) TSL_NS::details::JOIN__< __VA_ARGS__ >
/////////////////////////////////////////////////////////////////////////////////////

#endif /* JOINHELPER_H_ */
