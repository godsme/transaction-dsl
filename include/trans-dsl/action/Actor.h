/*
 * Actor.h
 *
 * Created on: Jul 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTOR_H_
#define ACTOR_H_

#define USE_ACTOR(P_ACTOR_TYPE) \
   virtual P_ACTOR_TYPE* getActor(const TransactionInfo&) = 0

#define ACTOR() getActor(trans)

#define DEF_ACTOR_BASED_ACTION(P_ACTOR_TYPE, P_BASE_ACTION) \
   template <typename P_ACTOR>                             \
   struct P_BASE_ACTION##__onto : P_BASE_ACTION                \
   {                                                       \
      P_ACTOR_TYPE* getActor(const TransactionInfo& trans) \
      { return P_ACTOR()(trans); }                         \
   }

#endif /* ACTOR_H_ */
