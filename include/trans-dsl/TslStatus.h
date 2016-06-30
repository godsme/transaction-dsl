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

    TSL_RESERVED_FAILURE = cub::CUB_RESERVED_FAILURE,

	__TSL_STATUS_BEGIN = 100,

    TSL_CONTINUE       = cub::succStatus(__TSL_STATUS_BEGIN),
    TSL_UNKNOWN_EVENT,

	TSL_OUT_OF_SCOPE   = cub::failStatus(__TSL_STATUS_BEGIN),
	TSL_DUPTID,
	TSL_INVALID_DATA,
	TSL_TIMEDOUT,
	TSL_RESTART_REQUIRED,
	TSL_NOTHING_CHANGED,

	TSL_FORCE_STOPPED

};

#endif /* INCLUDE_TRANS_DSL_TSLSTATUS_H_ */
