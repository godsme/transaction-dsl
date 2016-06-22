/*
 * TslStatus.h
 *
 *  Created on: Jun 22, 2016
 *      Author: darwin
 */

#ifndef INCLUDE_TRANS_DSL_TSLSTATUS_H_
#define INCLUDE_TRANS_DSL_TSLSTATUS_H_

#include <trans-dsl/tsl.h>
#include <cub/base/Status.h>

enum TslStatus : cub::Status
{
	TSL_SUCCESS   = CUB_SUCCESS,
	TSL_FATAL_BUG = CUB_FATAL_BUG,
	TSL_FAILED    = CUB_FAILURE,

	__TSL_STATUS_BEGIN = 100,

	TSL_CONTINUE       = __TSL_STATUS_BEGIN,
	TSL_UNKNOWN_EVENT,
	TSL_OUT_OF_SCOPE,
	TSL_DUPTID,
	TSL_INVALID_DATA

};

#endif /* INCLUDE_TRANS_DSL_TSLSTATUS_H_ */
