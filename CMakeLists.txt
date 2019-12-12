cmake_minimum_required(VERSION 3.14)
project(ci)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

file(
        GLOB Project_SRC
        "${PROJECT_SOURCE_DIR}/CTest/*"
        "${PROJECT_SOURCE_DIR}/Parser/*"
        "${PROJECT_SOURCE_DIR}/TestCase/*"
        "${PROJECT_SOURCE_DIR}/TestGeneration/*"
        "${PROJECT_SOURCE_DIR}/WebTest/*"
)

add_executable(ci ${Project_SRC})
target_link_libraries(ci sqlite3 sqlpp11 ${Boost_LIBRARIES})
