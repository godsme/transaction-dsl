/*
 * WaitOn.h
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef WAITON_H_
#define WAITON_H_

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
#define __WAIT_EVENT(...) do { \
   cub::Status ___wait_on_status__ = __VA_ARGS__; \
   if( ___wait_on_status__ != TSL_SUCCESS) return ___wait_on_status__; \
} while(0)

#define __WAIT_ON(eventId, handler, forever) \
   __WAIT_EVENT(waitOn(eventId, this, &ThisType::handler, forever))
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
#define WAIT_ON(eventId, handler) \
   __WAIT_ON(eventId, handler, false)

#define WAIT_ON_FOREVER(eventId, handler) \
   __WAIT_ON(eventId, handler, true)

#define PEEK_EVENT(eventId) \
   __WAIT_EVENT(waitUntouchEvent(eventId))
/////////////////////////////////////////////////////////////

#endif /* WAITON_H_ */
