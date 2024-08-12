# Test_VERSION_MAJOR and Test_VERSION_MINOR 
project(Test VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

add_executable(Test 
    main.c
    tests/dynamic_array/dynamic_array_test.c
    tests/image/image_test.c
    tests/io/io_test.c
    tests/linked_list/linked_list_test.c
    tests/thread/thread_test.c
    tests/time/time_test.c
    tests/unordered_map/unordered_map_test.c
    tests/window/window_test.c
)

target_include_directories(Test 
        PUBLIC "${PROJECT_SOURCE_DIR}/src/"
    )

target_link_libraries(Test
        PUBLIC Istd 
    )
