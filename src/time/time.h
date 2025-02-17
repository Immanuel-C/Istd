#pragma once

#include "core.h"


ISTD_EXTERN_C

#include <stdint.h>

ISTD_DEFINE_HANDLE(istd_timer);

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
ISTD_API istd_timer istd_timer_start(void);

/**
* @brief get the time since the timer was started
* @param timer The timer handle
* @param unit the timer unit that the timer will return
* @returns the time since the timer was started
*/
ISTD_API double istd_timer_now(
	istd_timer timer,
	istd_time_units unit
);


/**
* @brief get the time since the timer was started and free it
* @param timer the timer handle
* @param unit the timer unit that the timer will return
* @returns the timer since the timer was started
*/
ISTD_API double istd_timer_end(
	istd_timer timer,
	istd_time_units unit
);

ISTD_END_EXTERN_C
