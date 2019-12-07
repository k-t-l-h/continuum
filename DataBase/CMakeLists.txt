cmake_minimum_required(VERSION 3.15)
project(test_db)

set(CMAKE_CXX_STANDARD 14)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/submodules")

include_directories(
        submodules/date/include
        submodules/date/include/date
        submodules/sqlpp11/include
        submodules/sqlpp11-connector-sqlite3/include
)

find_package(SQLite3 REQUIRED)

set(HinnantDate_ROOT_DIR "${LIB_DIR}/date/include")
set(Sqlite3_DIR "${LIB_DIR}/libsqlite3")
set(Sqlpp11_DIR "${LIB_DIR}/sqlpp11")
set(Sqlpp11Sqlite3_DIR "${LIB_DIR}/sqlpp11-connector-sqlite3")

add_subdirectory(${Sqlpp11_DIR})
add_subdirectory(${Sqlpp11Sqlite3_DIR})

file(
        GLOB Backend_SRC
        "${SRC_DIR}/*.h"
        "${SRC_DIR}/*.cpp"
        "${Sqlpp11Sqlite3_DIR}/src/*.h"
        "${Sqlpp11Sqlite3_DIR}/src/*.cpp"
        "${Sqlpp11Sqlite3_DIR}/src/detail/*.h"
        "${Sqlpp11Sqlite3_DIR}/src/detail/*.cpp"
)

add_executable(ogma_backend ${Backend_SRC} Database.cpp Database.h)
target_link_libraries(ogma_backend sqlite3 sqlpp11)
