/*
 * SimpleAsyncActionHelper.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLEASYNCACTIONHELPER_H_
#define SIMPLEASYNCACTIONHELPER_H_

#include "trans-dsl/action/SimpleAsyncAction.h"
#include "trans-dsl/utils/WaitOn.h"

/////////////////////////////////////////////////////////////
namespace details
{
   template<typename T_ACTION>
   struct GenericSimpleAsyncAction: SimpleAsyncAction
   {
   protected:
      typedef T_ACTION ThisType;
   };
}

#define DEF_SIMPLE_ASYNC_ACTION(action) \
   struct action : details::GenericSimpleAsyncAction<action>

/////////////////////////////////////////////////////////////
#define __ACTION_REAL_HANLDER(handler) actual_##handler

#define ACTION_SIMPLE_EVENT_HANDLER_DECL(handler, EventType) \
   Status handler(const TransactionInfo&, const Event&); \
   Status __ACTION_REAL_HANLDER(handler)(const TransactionInfo&, const EventType&)

#define ACTION_SIMPLE_EVENT_HANDLER_DEF(ActionClass, handler, EventType) \
   Status ActionClass::handler(const TransactionInfo& trans, const Event& event) \
   { \
      return __ACTION_REAL_HANLDER(handler)(trans, *((const EventType*)event.getMsg())); \
   } \
   Status ActionClass::__ACTION_REAL_HANLDER(handler)(const TransactionInfo& trans, const EventType& event)

#endif /* SIMPLEASYNCACTIONHELPER_H_ */

