#include "monitor_win32.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellscalingapi.h>


#include "allocator/allocator.h"
#include "safe/string_safe.h"

#include <stdlib.h>

typedef struct {
	HMONITOR hmonitor;
	istd_vector2_i32 size;
	istd_vector2_i32 position;
	istd_vector2_i32 dpi;
	wchar_t name[CCHDEVICENAME]; // CCHDEVICENAME is provided by Windows.h. The length the monitors name is always same or less to this macro.
	istd_allocator allocator;
} __istd_monitor_win32;


istd_monitor_win32 istd_monitor_win32_primary(
	_In_opt_ istd_allocator* allocator
) {
	istd_allocator* alloc = allocator;

	if (alloc == istd_nullptr)
		alloc = istd_get_defualt_allocator();

	// The primary monitors top left corner is always 0, 0
	HMONITOR hmonitor = MonitorFromPoint((POINT){ 0 }, MONITOR_DEFAULTTOPRIMARY);

	MONITORINFOEXW monitor_info = { 0 };
	monitor_info.cbSize = sizeof(MONITORINFOEXW);

	if (GetMonitorInfoW(hmonitor, (LPMONITORINFO)&monitor_info) == FALSE)
		return istd_nullhnd;
	
	__istd_monitor_win32* monitor = alloc->malloc(sizeof(__istd_monitor_win32));

	if (monitor == istd_nullptr)
		return istd_nullhnd;

	monitor->size = (istd_vector2_i32){ (int32_t)(monitor_info.rcMonitor.right - monitor_info.rcMonitor.left), (int32_t)(monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) };
	monitor->position = (istd_vector2_i32){ (int32_t)(monitor_info.rcMonitor.left), (int32_t)(monitor_info.rcMonitor.top) };
	
	UINT dpi_x = 0, dpi_y = 0;
	if (GetDpiForMonitor(hmonitor, MDT_EFFECTIVE_DPI, &dpi_x, &dpi_y) != S_OK) {
		alloc->free(monitor);
		return istd_nullhnd;
	}

	monitor->dpi = (istd_vector2_i32){ (int32_t)(dpi_x), (int32_t)(dpi_y) };

	if (istd_wcscpy_safe(monitor->name, CCHDEVICENAME, monitor_info.szDevice) != ISTD_ENONE) {
		alloc->free(monitor);
		return istd_nullhnd;
	}

	monitor->allocator = *alloc;
	
	return (istd_monitor_win32)monitor;
}

static BOOL CALLBACK monitor_callback_count(HMONITOR hmonitor, HDC hdc, LPRECT monitor_rect, LPARAM user_data) {
	istd_unused_parameter(hmonitor);
	istd_unused_parameter(hdc);
	istd_unused_parameter(monitor_rect);

	size_t* count = (size_t*)user_data;
	(*count)++;
	return TRUE;
}

size_t istd_monitor_win32_count(void) {
	size_t count = 0;
	if (EnumDisplayMonitors(istd_nullptr, istd_nullptr, monitor_callback_count, (LPARAM)&count) == FALSE)
		return SIZE_MAX;

	return count;
}

typedef struct {
	__istd_monitor_win32** monitors;
	size_t index;
} __istd_monitor_callback_info;

static BOOL CALLBACK monitor_callback(HMONITOR hmonitor, HDC hdc, LPRECT monitor_rect, LPARAM user_data) {
	istd_unused_parameter(hdc);
	istd_unused_parameter(monitor_rect);

	__istd_monitor_callback_info* callback_info = (__istd_monitor_callback_info*)user_data;

	MONITORINFOEX monitor_info = { 0 };
	monitor_info.cbSize = sizeof(MONITORINFOEX);

	if (GetMonitorInfoW(hmonitor, (LPMONITORINFO)&monitor_info) == FALSE)
		return FALSE;

	callback_info->monitors[callback_info->index]->hmonitor = hmonitor;
	callback_info->monitors[callback_info->index]->size = (istd_vector2_i32){ (int32_t)(monitor_info.rcMonitor.right - monitor_info.rcMonitor.left), (int32_t)(monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) };
	callback_info->monitors[callback_info->index]->position = (istd_vector2_i32){ (int32_t)(monitor_info.rcMonitor.left), (int32_t)(monitor_info.rcMonitor.top) };

	UINT dpi_x = 0, dpi_y = 0;
	if (GetDpiForMonitor(hmonitor, MDT_EFFECTIVE_DPI, &dpi_x, &dpi_y) != S_OK) {
		return FALSE;
	}

	callback_info->monitors[callback_info->index]->dpi = (istd_vector2_i32){ (int32_t)(dpi_x), (int32_t)(dpi_y) };

	if (istd_wcscpy_safe(callback_info->monitors[callback_info->index]->name, CCHDEVICENAME, monitor_info.szDevice) != ISTD_ENONE)
		return FALSE;

	callback_info->index++;

	return TRUE;
}

istd_monitor_win32* istd_monitor_win32_all(
	_In_	 size_t* monitor_count,
	_In_opt_ istd_allocator* allocator
) {
	istd_allocator* alloc = allocator;

	if (alloc == istd_nullptr)
		alloc = istd_get_defualt_allocator();

	(*monitor_count) = istd_monitor_win32_count();

	if ((*monitor_count) == SIZE_MAX)
		return istd_nullptr;

	__istd_monitor_win32** monitors = alloc->malloc((*monitor_count) * sizeof(__istd_monitor_win32*));

	if (monitors == istd_nullptr)
		return istd_nullptr;

	for (size_t i = 0; i < (*monitor_count); i++) {
		monitors[i] = alloc->malloc(sizeof(__istd_monitor_win32));

		if (monitors[i] == istd_nullptr) 
			for (size_t y = 0; y == i; y++) 
				alloc->free(monitors[y]);

		monitors[i]->allocator = *alloc;
	}

	__istd_monitor_callback_info callback_info = { 0 };
	callback_info.monitors = monitors;
	callback_info.index = 0;

	if (EnumDisplayMonitors(istd_nullptr, istd_nullptr, monitor_callback, (LPARAM)&callback_info) == FALSE) {
		for (size_t i = 0; i < (*monitor_count); i++)
			alloc->free(monitors[i]);

		alloc->free(monitors);

		return istd_nullptr;
	}

	return (istd_monitor_win32*)monitors;
}

const wchar_t* istd_monitor_win32_name(
	_In_ istd_monitor_win32 monitor
) {
	return (const wchar_t*)((__istd_monitor_win32*)monitor)->name;
}

istd_vector2_i32 istd_monitor_win32_size(
	_In_ istd_monitor_win32 monitor
) {
	return ((__istd_monitor_win32*)monitor)->size;
}

istd_vector2_i32 istd_monitor_win32_position(
	_In_ istd_monitor_win32 monitor
) {
	return ((__istd_monitor_win32*)monitor)->position;
}

istd_vector2_i32 istd_monitor_win32_dpi(
	_In_ istd_monitor_win32 monitor
) {
	return ((__istd_monitor_win32*)monitor)->dpi;
}

uintptr_t istd_monitor_win32_hmonitor(
	_In_ istd_monitor_win32 monitor
) {
	return (uintptr_t)(((__istd_monitor_win32*)monitor)->hmonitor);
}

void istd_monitor_win32_free(
	_In_ istd_monitor_win32* monitors,
	_In_ size_t monitors_count
) {
	for (size_t i = 0; i < monitors_count; i++) {
		__istd_monitor_win32* _monitor = (__istd_monitor_win32*)monitors[i];
		_monitor->allocator.free(_monitor);
	}
}