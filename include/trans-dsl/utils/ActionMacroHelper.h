/*
 * ActionMacroHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONMACROHELPER_H_
#define ACTIONMACROHELPER_H_

#include <base/utils/RepeatMacros.h>
#include <trans-dsl/utils/DummyAction.h>

#define __ARG(n)              ACTION ## n

#define __TEMPLATE_ARG(n)       typename __ARG(n)
#define __TEMPLATE_ARGS(n)      __TEMPLATE_ARG(n),

#define DECL_TEMPLATE_ARGS(n) REPEAT(n, __TEMPLATE_ARGS, __TEMPLATE_ARG)

////////////////////////////////////////////////////////////////
#define __MEMBER_DEF(n)  details::LINKED__< __ARG(n) > action ## n;

#define DECL_MEMBERS(n) SIMPLE_REPEAT(n, __MEMBER_DEF)

////////////////////////////////////////////////////////////////
#define __REPEAT_ARGS(n)  __ARG(n),
#define ACTION_ARGS(n) SIMPLE_REPEAT(n, __REPEAT_ARGS)

////////////////////////////////////////////////////////////////
#define __DUMMY_ACTION(n)  details::DummyAction
#define __REPEAT_DUMMY_ACTION(n) details::DummyAction,
#define DUMMY_ARGS(n) REPEAT(n, __REPEAT_DUMMY_ACTION, __DUMMY_ACTION)

////////////////////////////////////////////////////////////////
#define __WITH_DUMMY_DEFAULT(n) __TEMPLATE_ARG(n) = details::DummyAction
#define __REPEAT_DUMMY_DEFAULT(n) __WITH_DUMMY_DEFAULT(n),

#define DECL_DUMMY_DEFAULT(n) REPEAT(n, __REPEAT_DUMMY_DEFAULT, __WITH_DUMMY_DEFAULT)

///////////////////////////////////////////////////////////////
#define DECL_ALL_ARGS(n) REPEAT(n, __REPEAT_ARGS, __ARG)

#endif /* ACTIONMACROHELPER_H_ */
