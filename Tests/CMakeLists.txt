cmake_minimum_required(VERSION 3.1)
project(Tests CXX)

include(ExternalProject)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES TestsManager.cpp TestsReporter.cpp)

add_executable(Tests ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main gmock gmock_main)