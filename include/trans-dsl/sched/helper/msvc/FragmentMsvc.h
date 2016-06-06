/*
 * FragmentMsvc.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FRAGMENTMSVC_H_
#define FRAGMENTMSVC_H_

////////////////////////////////////////////////////
#define __DEF1(...) \
   template<bool _Dummy_N_, ##__VA_ARGS__ >

#define __def(name, ...) __DEF1(__VA_ARGS__) struct name
#define __params(...)      __VA_ARGS__
#define __as(...)  : __VA_ARGS__ {}


//////////////////////////////////////////////////////////////
#define __APPLY1(...) < true, ##__VA_ARGS__ >

#define __apply(name, ...) name __APPLY1(__VA_ARGS__)
#define __with(...) __VA_ARGS__

#endif /* FRAGMENTMSVC_H_ */
