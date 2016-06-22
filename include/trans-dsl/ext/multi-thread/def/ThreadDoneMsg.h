/*
 * ThreadDoneMsg.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef THREADDONEMSG_H_
#define THREADDONEMSG_H_

#include <trans-dsl/ext/multi-thread/concept/ActionThreadId.h>
#include <event/concept/EventId.h>
#include <cub/base/Status.h>

TSL_NS_BEGIN

const ev::EventId EV_ACTION_THREAD_DONE = 0xFFFE;

struct ThreadDoneMsg
{
   ThreadDoneMsg(ActionThreadId who, cub::Status status)
     : who(who)
     , result(status)
   {}

   const ActionThreadId who;
   const cub::Status    result;
};

TSL_NS_END

#endif /* THREADDONEMSG_H_ */
