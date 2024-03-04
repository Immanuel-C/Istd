#include "time.h"

#include <time.h>

#include <stdlib.h>

typedef struct _istd_timer_t {
	clock_t start;
} _istd_timer;


istd_timer istd_timer_start(void) {
	_istd_timer* timer = malloc(sizeof(_istd_timer));
	if (timer == istd_nullptr) return istd_nullptr;

	timer->start = clock();

	if (timer->start == -1) {
		free(timer);
		return istd_nullptr;
	}

	return (istd_timer)timer;
}

double istd_timer_now(
	_In_ istd_timer timer,
	_In_ istd_time_units unit
) { 
	_istd_timer* _timer = (_istd_timer*)timer;
	clock_t end = clock();

	if (end == -1) return -1.0;

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

double istd_timer_end(
	_Inout_ istd_timer timer,
	_In_    istd_time_units unit
) {
	double delta = istd_timer_now(timer, unit);
	free((_istd_timer*)timer);
	timer = istd_nullptr;
	return delta;
}
