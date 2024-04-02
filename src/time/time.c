#include "time.h"

#include <time.h>

#include <stdlib.h>

typedef struct {
	clock_t start;
} __istd_timer;


istd_timer istd_timer_start(void) {
	__istd_timer* timer = malloc(sizeof(__istd_timer));
	if (timer == istd_nullptr) return istd_nullptr;

	timer->start = clock();

	if (timer->start == -1) {
		free(timer);
		return istd_nullptr;
	}

	return (istd_timer)timer;
}

istd_float64 istd_timer_now(
	_In_ istd_timer timer,
	_In_ istd_time_units unit
) { 
	__istd_timer* _timer = (__istd_timer*)timer;
	clock_t end = clock();

	if (end == -1) return 0.0;

	double time_seconds = (double)(end - _timer->start) / CLOCKS_PER_SEC;

	switch (unit)
	{
	case ISTD_NANOSECONDS:
		return time_seconds * 1000000000.0;
	case ISTD_MILISECONDS:
		return time_seconds * 1000.0;
	case ISTD_SECONDS:
		return time_seconds;
	case ISTD_MINUTES:
		return time_seconds / 60.0;
	default:
		break;
	}

	return -1.0;
}

istd_float64 istd_timer_end(
	_Inout_ istd_timer timer,
	_In_    istd_time_units unit
) {
	double delta = istd_timer_now(timer, unit);
	free((__istd_timer*)timer);
	timer = istd_nullptr;
	return delta;
}
