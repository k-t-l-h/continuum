cmake_minimum_required(VERSION 3.1)
project(continuum CXX)

include(ExternalProject)



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/DataBase/submodules")

include_directories(
        DataBase/submodules/date/include
        DataBase/submodules/date/include/date
        DataBase/submodules/sqlpp11/include
        DataBase/submodules/sqlpp11-connector-sqlite3/include
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

        "${Sqlpp11Sqlite3_DIR}/src/*.h"
        "${Sqlpp11Sqlite3_DIR}/src/*.cpp"
        "${Sqlpp11Sqlite3_DIR}/src/detail/*.h"
        "${Sqlpp11Sqlite3_DIR}/src/detail/*.cpp"
)

#set(${Boost_INCLUDE_DIRS} /home/evgeny/boost_1_71_0/)

find_package(Boost REQUIRED )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable( ci ${Backend_SRC} TestCase/TestCaseClass.cpp TestCase/CTestCase.cpp TestCase/WebTestCase.cpp
        TestGeneration/testgen.cpp CTest/ctestgen.cpp WebTest/webtestgen.cpp Parser/parser.cpp
        Container/Container.cpp Manager/Manager.cpp Reporter/Reporter.cpp DataBase/DataBase.cpp General/General.cpp ${Backend_SRC})

target_link_libraries(ci sqlite3 sqlpp11 ${Boost_LIBRARIES})


