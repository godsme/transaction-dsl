/*
 * ConcurrentHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef CONCURRENTHELPER_H_
#define CONCURRENTHELPER_H_

#include "trans-dsl/sched/action/SchedConcurrentAction.h"
#include "trans-dsl/sched/helper/LinkedThreadHelper.h"
#include "trans-dsl/sched/helper/VoidHelper.h"

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include "trans-dsl/sched/helper/11/Concurrent11.h"
#else
#include "trans-dsl/sched/helper/98/Concurrent98.h"
#endif

/////////////////////////////////////////////////////////////////////////////////
#define __concurrent(...) \
       TSL_NS::details::CONCURRENT__< __VA_ARGS__ >

#define __void_concurrent(...) \
       TSL_NS::details::VOID_CONCURRENT__< __VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////////

#endif /* CONCURRENTHELPER_H_ */
