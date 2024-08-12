#include "vulkan/vulkan_core.h"
#if !defined(ISTD_WINDOW_VULKAN_H)
#define ISTD_WINDOW_VULKAN_H

#include "core.h"

ISTD_EXTERN_C

#include "window.h"

#include <vulkan/vulkan.h>

/**
* @brief This function creates a handle to a VkSurfaceKHR. 
* @param window A valid istd_window created by istd_window_create.
* @param instance A handle to a valid VkIntstance created by VkCreateInstance.
* @param surface A pointer to an empty Vulkan surface handle.  
* @returns the value of vkCreateXXXXXSurfaceKHR (see https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#_wsi_surface).
*/
istd_api VkResult istd_window_vk_surface_create(
        istd_window window, 
        VkInstance instance, 
        VkSurfaceKHR* surface
    );

ISTD_END_EXTERN_C

#endif
