cmake_minimum_required(VERSION 3.12)
project(mcu_verso)

set(CMAKE_CXX_STANDARD 17)

option(VERSO_BUILD_TEST     "Build tests for lest" ON)

include_directories(include)
include_directories(src/test/include)

if (VERSO_BUILD_TEST)
    add_subdirectory(src/test)
endif()

enable_testing()

add_executable(mcu_verso
        include/conditional.h
        src/test/test_library.cpp include/container.h include/util.h include/gcode.h include/estring.h)
