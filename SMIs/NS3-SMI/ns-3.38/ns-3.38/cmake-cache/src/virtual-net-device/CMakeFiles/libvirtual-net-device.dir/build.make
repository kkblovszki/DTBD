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
include src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/compiler_depend.make

# Include the progress variables for this target.
include src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/progress.make

# Include the compile flags for this target's objects.
include src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/flags.make

# Object files for target libvirtual-net-device
libvirtual__net__device_OBJECTS =

# External object files for target libvirtual-net-device
libvirtual__net__device_EXTERNAL_OBJECTS = \
"/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/virtual-net-device/CMakeFiles/libvirtual-net-device-obj.dir/model/virtual-net-device.cc.o"

../build/lib/libns3.38-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/libvirtual-net-device-obj.dir/model/virtual-net-device.cc.o
../build/lib/libns3.38-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/build.make
../build/lib/libns3.38-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library ../../../build/lib/libns3.38-virtual-net-device-debug.so"
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/virtual-net-device && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libvirtual-net-device.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/build: ../build/lib/libns3.38-virtual-net-device-debug.so
.PHONY : src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/build

src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/clean:
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/virtual-net-device && $(CMAKE_COMMAND) -P CMakeFiles/libvirtual-net-device.dir/cmake_clean.cmake
.PHONY : src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/clean

src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/depend:
	cd /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38 /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/virtual-net-device /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/virtual-net-device /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/cmake-cache/src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/virtual-net-device/CMakeFiles/libvirtual-net-device.dir/depend

