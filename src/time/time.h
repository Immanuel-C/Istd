#pragma once

#include "core.h"

ISTD_EXTERN_C

#include <stdint.h>

istd_define_handle(istd_timer);

/**
* @brief Used to specify time units for timers.
*/
typedef enum istd_time_units_values {
	ISTD_NANOSECONDS,
	ISTD_MILISECONDS,
	ISTD_SECONDS,
	ISTD_MINUTES
} istd_time_units;

/**
* Star
*/
istd_api istd_timer istd_stdcall istd_timer_start(void);

istd_api double istd_stdcall istd_timer_now(
	_In_ istd_timer timer,
	_In_ istd_time_units unit
);

istd_api double istd_stdcall istd_timer_end(
	_Inout_ istd_timer timer,
	_In_    istd_time_units unit
);

ISTD_END_EXTERN_C