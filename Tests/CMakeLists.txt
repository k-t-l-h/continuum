cmake_minimum_required(VERSION 3.1)
project(Tests CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES UnitTestsReporter.cpp UnitTestsManager.cpp TestsManager.cpp TestsReporter.cpp)

add_executable(Tests ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main gmock gmock_main)