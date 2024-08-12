project(Istd VERSION 1.0)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

if(WIN32)
    set(OS_SOURCES 
        window/win32/monitor_win32.c
        window/win32/window_win32.c
    )
endif()

option(USE_VULKAN "Compile Istd with with vulkan" ON)

if (USE_VULKAN)
    find_package(Vulkan REQUIRED)
    set(VULKAN_SOURCES "window/vulkan.c")
endif()

add_library(Istd STATIC 
        allocator/allocator.c
        dynamic_array/dynamic_array.c
        hash_map/unordered_map.c
        image/image.c
        io/io.c
        linked_list/singly_linked_list.c
        safe/string_safe.c
        test/test.c
        thread/thread.c
        time/high_resolution.c
        time/time.c
        window/window.c
        window/window_enums.c
        window/monitor.c
        ${OS_SOURCES}
        ${VULKAN_SOURCES}
    )

target_include_directories(Istd 
        PUBLIC  ${PROJECT_SOURCE_DIR}
        PRIVATE ${Vulkan_INCLUDE_DIRS}
    )

if(WIN32)
    target_link_libraries(Istd
            PRIVATE Kernel32
            PRIVATE Shcore
            PRIVATE Gdi32
            PRIVATE ${Vulkan_LIBRARIES}
        )
endif(WIN32)


