#include "high_resolution.h"


#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Unix/Posix
#else



#endif

uint64_t istd_high_resolution_now_ns(void) {

	#if defined(_WIN32)
	LARGE_INTEGER counter, freq;

	if (QueryPerformanceFrequency(&freq) == FALSE)
		return 0;
	if (QueryPerformanceCounter(&counter) == FALSE)
		return 0;

	// Convert to nanoseconds
	counter.QuadPart *= (LONGLONG)1000000000;
	counter.QuadPart /= freq.QuadPart;

	return (uint64_t)counter.QuadPart;

	#else

	// CLOCK_BOOTTIME_ALARM 
	// clock_gettime

	#endif

}