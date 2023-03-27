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
CMAKE_SOURCE_DIR = /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache

# Include any dependencies generated for this target.
include src/antenna/CMakeFiles/libantenna.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/antenna/CMakeFiles/libantenna.dir/compiler_depend.make

# Include the progress variables for this target.
include src/antenna/CMakeFiles/libantenna.dir/progress.make

# Include the compile flags for this target's objects.
include src/antenna/CMakeFiles/libantenna.dir/flags.make

# Object files for target libantenna
libantenna_OBJECTS =

# External object files for target libantenna
libantenna_EXTERNAL_OBJECTS = \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/angles.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/antenna-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/cosine-antenna-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/isotropic-antenna-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/parabolic-antenna-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/phased-array-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/three-gpp-antenna-model.cc.o" \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna-obj.dir/model/uniform-planar-array.cc.o"

../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/angles.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/antenna-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/cosine-antenna-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/isotropic-antenna-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/parabolic-antenna-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/phased-array-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/three-gpp-antenna-model.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna-obj.dir/model/uniform-planar-array.cc.o
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna.dir/build.make
../build/lib/libns3.38-antenna-debug.so: src/antenna/CMakeFiles/libantenna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library ../../../build/lib/libns3.38-antenna-debug.so"
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libantenna.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/antenna/CMakeFiles/libantenna.dir/build: ../build/lib/libns3.38-antenna-debug.so
.PHONY : src/antenna/CMakeFiles/libantenna.dir/build

src/antenna/CMakeFiles/libantenna.dir/clean:
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna && $(CMAKE_COMMAND) -P CMakeFiles/libantenna.dir/cmake_clean.cmake
.PHONY : src/antenna/CMakeFiles/libantenna.dir/clean

src/antenna/CMakeFiles/libantenna.dir/depend:
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38 /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/antenna /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/antenna/CMakeFiles/libantenna.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/antenna/CMakeFiles/libantenna.dir/depend

