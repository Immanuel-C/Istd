project(Test VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

option(ISTD_BUILD_TEST ON)

if (ISTD_BUILD_TEST)

    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra")
    endif()
    if (MSVC)
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /W4")
    endif()

    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

    add_executable(Test 
        main.c
        tests/dynamic_array/dynamic_array_test.c
        tests/linked_list/linked_list_test.c
        tests/thread/thread_test.c
        tests/time/time_test.c
        tests/unordered_map/unordered_map_test.c
    )

    target_include_directories(Test 
        PUBLIC "${PROJECT_SOURCE_DIR}/src/"
    )

    target_link_libraries(Test
        PUBLIC Istd 
    )

endif()
