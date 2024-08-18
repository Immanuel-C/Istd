project(Istd VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

add_library(Istd STATIC 
        allocator/allocator.c
        dynamic_array/dynamic_array.c
        hash_map/unordered_map.c
        io/io.c
        linked_list/singly_linked_list.c
        safe/string_safe.c
        test/test.c
        thread/thread.c
        time/high_resolution.c
        time/time.c
    )

target_include_directories(Istd 
        PUBLIC  ${PROJECT_SOURCE_DIR}
    )

if(WIN32)
    target_link_libraries(Istd
            PRIVATE Kernel32
            PRIVATE Shcore
            PRIVATE Gdi32
        )
endif(WIN32)


