# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/evgeny/CI-SERVER

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/evgeny/CI-SERVER/build

# Include any dependencies generated for this target.
include libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/depend.make

# Include the progress variables for this target.
include libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/progress.make

# Include the compile flags for this target's objects.
include libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/flags.make

libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o: libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/flags.make
libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o: ../libs/sqlpp11-connector-sqlite3/tests/AttachTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evgeny/CI-SERVER/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o"
	cd /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o -c /home/evgeny/CI-SERVER/libs/sqlpp11-connector-sqlite3/tests/AttachTest.cpp

libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.i"
	cd /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evgeny/CI-SERVER/libs/sqlpp11-connector-sqlite3/tests/AttachTest.cpp > CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.i

libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.s"
	cd /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evgeny/CI-SERVER/libs/sqlpp11-connector-sqlite3/tests/AttachTest.cpp -o CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.s

# Object files for target Sqlpp11Sqlite3AttachTest
Sqlpp11Sqlite3AttachTest_OBJECTS = \
"CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o"

# External object files for target Sqlpp11Sqlite3AttachTest
Sqlpp11Sqlite3AttachTest_EXTERNAL_OBJECTS =

libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest: libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/AttachTest.cpp.o
libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest: libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/build.make
libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest: libs/sqlpp11-connector-sqlite3/src/libsqlpp11-connector-sqlite3.a
libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest: /usr/lib/x86_64-linux-gnu/libsqlite3.so
libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest: libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/evgeny/CI-SERVER/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/Sqlpp11Sqlite3AttachTest"
	cd /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/build: libs/sqlpp11-connector-sqlite3/bin/Sqlpp11Sqlite3AttachTest

.PHONY : libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/build

libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/clean:
	cd /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests && $(CMAKE_COMMAND) -P CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/cmake_clean.cmake
.PHONY : libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/clean

libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/depend:
	cd /home/evgeny/CI-SERVER/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/evgeny/CI-SERVER /home/evgeny/CI-SERVER/libs/sqlpp11-connector-sqlite3/tests /home/evgeny/CI-SERVER/build /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests /home/evgeny/CI-SERVER/build/libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/sqlpp11-connector-sqlite3/tests/CMakeFiles/Sqlpp11Sqlite3AttachTest.dir/depend

