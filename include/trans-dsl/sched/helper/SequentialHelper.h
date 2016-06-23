/*
 * SequentialHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SEQUENTIALHELPER_H_
#define SEQUENTIALHELPER_H_

#include <trans-dsl/sched/action/SchedSequentialAction.h>
#include <trans-dsl/sched/helper/LinkedHelper.h>
#include <trans-dsl/sched/helper/VoidHelper.h>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <trans-dsl/sched/helper/11/Sequential11.h>
#else
#include <trans-dsl/sched/helper/98/Sequential98.h>
#endif

/////////////////////////////////////////////////////////////////////////////////
#define __sequential(...)      \
       TSL_NS::details::SEQUENTIAL__< __VA_ARGS__ >

#define __void_sequential(...) \
       TSL_NS::details::VOID_SEQUENTIAL__< __VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////////

#endif /* SEQUENTIALHELPER_H_ */
