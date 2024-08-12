#include "vulkan.h"
#include "vulkan/vulkan_core.h"

#if defined(_WIN32)
#include <windows.h>
#include <vulkan/vulkan_win32.h>

typedef struct {
	HWND hwnd;
	HDC hdc;
	HINSTANCE hinstance;
} platform_window_info;
#endif

istd_api VkResult istd_window_vk_surface_create(
        istd_window window, 
        VkInstance instance, 
        VkSurfaceKHR* surface
) {
    #if defined(_WIN32)

    platform_window_info* info = (platform_window_info*)(window);   

    VkWin32SurfaceCreateInfoKHR create_info = { 0 };
    create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    create_info.hwnd = info->hwnd;
    create_info.hinstance = info->hinstance;
    create_info.flags = 0;

    return vkCreateWin32SurfaceKHR(instance, &create_info, istd_nullptr, surface);
    
    #endif
}
