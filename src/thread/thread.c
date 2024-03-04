#include "thread.h"

// The C standard library does not include a sleep function and multithreading support but Linux and Windows does
// must link with Kernel32.
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN      
#include <windows.h>
#include <process.h>
typedef HANDLE istd_native_thread_handle;
#define _istd_native_sleep(mili) Sleep(mili)
// MacOs/Linux
#else
#error Istd does not support multi-threading on any other platform except windows for now.
#include <unistd.h>
#define _istd_native_sleep(mili) sleep(mili * 0.001)
#endif



istd_api void istd_stdcall istd_this_thread_sleep(
	_In_ uint32_t miliseconds
) {
	_istd_native_sleep(miliseconds);
}

istd_thread istd_thread_create(
	_In_	 istd_pfn_thread thread_fun,
	_In_opt_ void* thread_fun_arg
) {

	#if defined(_WIN32)

	istd_disable_warning(4191)
	istd_native_thread_handle thread_handle = (istd_native_thread_handle)_beginthreadex(istd_nullptr, 0, (_beginthreadex_proc_type)thread_fun, thread_fun_arg, 0, istd_nullptr);

	#else



	#endif
	
	return (istd_thread)thread_handle;
}

istd_thread_id istd_thread_get_id(
	_In_ istd_thread thread
) {
	#if defined(_WIN32)

	return GetThreadId((istd_native_thread_handle)thread);

	#else


	#endif
}

istd_thread_id istd_thread_get_current_id(void) {
	return GetCurrentThreadId();
}

void istd_thread_join(
	_Inout_ istd_thread thread
) {
	istd_native_thread_handle thread_handle = (istd_native_thread_handle)thread;

	#if defined(_WIN32)

	WaitForSingleObject(thread_handle, INFINITE);
	CloseHandle(thread_handle);

	thread = istd_nullptr;

	#else

	#endif
}
