cmake_minimum_required(VERSION 3.16)
project(OOP_3)
set(CMAKE_CXX_STANDARD 17)


add_executable(OOP_3
        src/main.cpp
        src/my_lib.cpp
)

target_include_directories(OOP_3 PRIVATE include)
target_link_options(OOP_3 PRIVATE -static -static-libgcc -static-libstdc++)

add_executable(vector_benchmark
        src/vector_benchmark.cpp
)

target_include_directories(vector_benchmark PRIVATE include)
target_link_options(vector_benchmark PRIVATE -static -static-libgcc -static-libstdc++)

if(NOT CMAKE_CROSSCOMPILING)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(testai
            tests/studentas_test.cpp
            tests/vector_test.cpp
            src/my_lib.cpp
    )

    target_include_directories(testai PRIVATE include)
    target_link_libraries(testai PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(testai)
endif()