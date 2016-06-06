/*
 * FragmentGnu.h
 *
 * Created on: Mar 1, 2014
 *     author: Darwin Yuan
 *
 * Copyright 2014 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FRAGMENTGNU_H_
#define FRAGMENTGNU_H_

#define __def(name, ...)  __VA_ARGS__ struct name
#define __params(...) template< __VA_ARGS__ >

#define __as(...)  : __VA_ARGS__ {}

//////////////////////////////////////////////////////////////
#define __apply(name, ...) name __VA_ARGS__
#define __with(...) <__VA_ARGS__ >


#endif /* FRAGGNU_H_ */
