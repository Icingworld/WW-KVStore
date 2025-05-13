cmake_minimum_required(VERSION 3.10)
project(ww-kvstore VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(kvstore)

option(WWTEST "Enable Test" ON)
option(WWBENCHMARK "Enable Benchmark" OFF)

if (WWTEST)
    message(STATUS "Test ON")
    add_subdirectory(third-party)
    add_subdirectory(test)
else()
    message(STATUS "Test OFF")
endif()