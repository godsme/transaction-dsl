/*
 * TransDsl.h
 *
 *  Created on: Jun 22, 2016
 *      Author: darwin
 */

#ifndef INCLUDE_TRANS_DSL_TSL_H_
#define INCLUDE_TRANS_DSL_TSL_H_

#define TSL_NS tsl
#define TSL_NS_BEGIN namespace TSL_NS {
#define TSL_NS_END   }
#define USING_TSL_NS using namespace TSL_NS;
#define FWD_DECL_TSL(type) namespace TSL_NS { struct type; }

#endif /* INCLUDE_TRANS_DSL_TSL_H_ */
