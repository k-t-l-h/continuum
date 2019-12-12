cmake_minimum_required(VERSION 3.14)
project(ci)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(LIB_DIR "${PROJECT_SOURCE_DIR}/libs")

include_directories(
        libs/date/include
        libs/date/include/date
        libs/sqlpp11/include
        libs/sqlpp11-connector-sqlite3/include
)

find_package(SQLite3 REQUIRED)

set(HinnantDate_ROOT_DIR "${LIB_DIR}/date/include")
set(Sqlite3_DIR "${LIB_DIR}/libsqlite3")
set(Sqlpp11_DIR "${LIB_DIR}/sqlpp11")
set(Sqlpp11Sqlite3_DIR "${LIB_DIR}/sqlpp11-connector-sqlite3")

add_subdirectory(${Sqlpp11_DIR})
add_subdirectory(${Sqlpp11Sqlite3_DIR})

file(
        GLOB Project_SRC
        "${PROJECT_SOURCE_DIR}/Container/*"
        "${PROJECT_SOURCE_DIR}/General/*"
        "${PROJECT_SOURCE_DIR}/Manager/*"
        "${PROJECT_SOURCE_DIR}/Reporter/*"
        "${PROJECT_SOURCE_DIR}/Database/*"
        "${PROJECT_SOURCE_DIR}/CTest/*"
        "${PROJECT_SOURCE_DIR}/Parser/*"
        "${PROJECT_SOURCE_DIR}/TestCase/*"
        "${PROJECT_SOURCE_DIR}/TestGeneration/*"
        "${PROJECT_SOURCE_DIR}/WebTest/*"
)

add_executable(ci ${Project_SRC})
target_link_libraries(ci sqlpp11-connector-sqlite3 sqlite3 sqlpp11 pthread ${Boost_LIBRARIES} -lboost_regex -lboost_iostreams)

