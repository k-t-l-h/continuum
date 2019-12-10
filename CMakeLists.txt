cmake_minimum_required(VERSION 3.1)
project(continuum CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/")

add_executable( ci ${Backend_SRC} TestCase/TestCaseClass.cpp TestCase/CTestCase.cpp TestCase/WebTestCase.cpp
        Container/Container.cpp ${Backend_SRC})