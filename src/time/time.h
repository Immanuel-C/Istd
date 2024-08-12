#pragma once

#include "core.h"

#include "istd_float.h"

ISTD_EXTERN_C

#include <stdint.h>

istd_define_handle(istd_timer);

/**
* @brief Used to specify time units for timers
*/
typedef enum istd_time_units_values {
	ISTD_NANOSECONDS,
	ISTD_MILISECONDS,
	ISTD_SECONDS,
	ISTD_MINUTES
} istd_time_units;

/**
* @brief Start timer
* @returns A timer handle
*/
istd_api istd_timer istd_timer_start(void);

/**
* @brief get the time since the timer was started
* @param timer The timer handle
* @param unit the timer unit that the timer will return
* @returns the time since the timer was started
*/
istd_api istd_float64 istd_timer_now(
	istd_timer timer,
	istd_time_units unit
);


/**
* @brief get the time since the timer was started and free it
* @param timer the timer handle
* @param unit the timer unit that the timer will return
* @returns the timer since the timer was started
*/
istd_api istd_float64 istd_timer_end(
	istd_timer timer,
	istd_time_units unit
);

ISTD_END_EXTERN_C
