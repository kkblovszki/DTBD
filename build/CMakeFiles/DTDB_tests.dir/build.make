# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Mikkel/Documents/GitHub/DTBD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build

# Include any dependencies generated for this target.
include CMakeFiles/DTDB_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DTDB_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DTDB_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DTDB_tests.dir/flags.make

CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o: CMakeFiles/DTDB_tests.dir/flags.make
CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o: ../test/add_test.cpp
CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o: CMakeFiles/DTDB_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o -MF CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o.d -o CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o -c /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/test/add_test.cpp

CMakeFiles/DTDB_tests.dir/test/add_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DTDB_tests.dir/test/add_test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/test/add_test.cpp > CMakeFiles/DTDB_tests.dir/test/add_test.cpp.i

CMakeFiles/DTDB_tests.dir/test/add_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DTDB_tests.dir/test/add_test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/test/add_test.cpp -o CMakeFiles/DTDB_tests.dir/test/add_test.cpp.s

# Object files for target DTDB_tests
DTDB_tests_OBJECTS = \
"CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o"

# External object files for target DTDB_tests
DTDB_tests_EXTERNAL_OBJECTS =

tests/bin/DTDB_tests: CMakeFiles/DTDB_tests.dir/test/add_test.cpp.o
tests/bin/DTDB_tests: CMakeFiles/DTDB_tests.dir/build.make
tests/bin/DTDB_tests: CMakeFiles/DTDB_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests/bin/DTDB_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DTDB_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DTDB_tests.dir/build: tests/bin/DTDB_tests
.PHONY : CMakeFiles/DTDB_tests.dir/build

CMakeFiles/DTDB_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DTDB_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DTDB_tests.dir/clean

CMakeFiles/DTDB_tests.dir/depend:
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mikkel/Documents/GitHub/DTBD /mnt/c/Users/Mikkel/Documents/GitHub/DTBD /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/build/CMakeFiles/DTDB_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DTDB_tests.dir/depend

