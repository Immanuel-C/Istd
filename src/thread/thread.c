#include "thread.h"

// The C standard library does not include a sleep function and multithreading support but Linux and Windows does
// must link with Kernel32.
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN      
#include <Windows.h>
#include <process.h>
typedef HANDLE istd_native_thread_handle;
#define __istd_native_sleep(mili) Sleep(mili)
// MacOs/Linux
#else
#include <unistd.h>
#include <pthread.h>
typedef pthread_t istd_native_thread_handle;
#define _istd_native_sleep(mili) sleep(mili * 0.001)
#endif


istd_api void istd_stdcall istd_this_thread_sleep(
    uint32_t miliseconds
) {
    __istd_native_sleep(miliseconds);
}

istd_thread istd_thread_create(
    istd_pfn_thread thread_fun,
    void* thread_fun_arg
) {

    #if defined(_WIN32)

    istd_disable_warning(4191)
    uintptr_t win32_thread_handle = _beginthreadex(istd_nullptr, 0, (_beginthreadex_proc_type)thread_fun, thread_fun_arg, 0, istd_nullptr);

    istd_native_thread_handle thread_handle = (istd_native_thread_handle)win32_thread_handle;

    #else
  
    istd_native_thread_handle thread_handle;

    if (pthread_create((pthread_t*)&thread_handle, istd_nullptr, thread_fun, thread_fun_arg) != 0) {
        return istd_nullptr;
    }

    #endif
    
    return (istd_thread)thread_handle;
}

istd_thread_id istd_thread_get_id(
    istd_thread thread
) {
    #if defined(_WIN32)

    return (istd_thread_id)GetThreadId((istd_native_thread_handle)thread);

    #else

    return (istd_thread_id)thread;

    #endif
}

istd_thread_id istd_thread_get_current_id(void) {
    #if defined(_WIN32)

    return (istd_thread_id)GetCurrentThreadId();

    #else

    return (istd_thread_id)pthread_self();

    #endif
}

void istd_thread_join(
    istd_thread thread
) {
    istd_native_thread_handle thread_handle = (istd_native_thread_handle)thread;

    #if defined(_WIN32)

    WaitForSingleObject(thread_handle, INFINITE);
    CloseHandle(thread_handle);

    #else

    pthread_join(thread_handle, istd_nullptr);
    thread = istd_nullptr;
  
    #endif
}
