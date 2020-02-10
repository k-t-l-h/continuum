# Install script for directory: /home/evgeny/CI-SERVER/libs/sqlpp11

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/evgeny/CI-SERVER/libs/sqlpp11/include/sqlpp11")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM RENAME "sqlpp11-ddl2cpp" FILES "/home/evgeny/CI-SERVER/libs/sqlpp11/scripts/ddl2cpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11/Sqlpp11Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11/Sqlpp11Targets.cmake"
         "/home/evgeny/CI-SERVER/build/libs/sqlpp11/CMakeFiles/Export/lib/cmake/Sqlpp11/Sqlpp11Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11/Sqlpp11Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11/Sqlpp11Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11" TYPE FILE FILES "/home/evgeny/CI-SERVER/build/libs/sqlpp11/CMakeFiles/Export/lib/cmake/Sqlpp11/Sqlpp11Targets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Sqlpp11" TYPE FILE FILES
    "/home/evgeny/CI-SERVER/libs/sqlpp11/cmake/Sqlpp11Config.cmake"
    "/home/evgeny/CI-SERVER/build/libs/sqlpp11/cmake/Sqlpp11ConfigVersion.cmake"
    "/home/evgeny/CI-SERVER/libs/sqlpp11/cmake/Modules/FindHinnantDate.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/tests/cmake_install.cmake")
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_types/cmake_install.cmake")
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_serializer/cmake_install.cmake")
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_static_asserts/cmake_install.cmake")
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_constraints/cmake_install.cmake")
  include("/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_scripts/cmake_install.cmake")

endif()

