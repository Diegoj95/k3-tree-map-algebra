# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /snap/cmake/1336/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1336/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build

# Include any dependencies generated for this target.
include external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/progress.make

# Include the compile flags for this target's objects.
include external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/flags.make

external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o: external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/flags.make
external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/sa_construct_test.cpp
external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o: external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o -MF CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o.d -o CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o -c /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/sa_construct_test.cpp

external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.i"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/sa_construct_test.cpp > CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.i

external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.s"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/sa_construct_test.cpp -o CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.s

# Object files for target sa_construct_test
sa_construct_test_OBJECTS = \
"CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o"

# External object files for target sa_construct_test
sa_construct_test_EXTERNAL_OBJECTS =

bin/sa_construct_test: external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/sa_construct_test.cpp.o
bin/sa_construct_test: external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/build.make
bin/sa_construct_test: lib/libsdsl.a
bin/sa_construct_test: lib/libgtest.a
bin/sa_construct_test: lib/libdivsufsort.a
bin/sa_construct_test: lib/libdivsufsort64.a
bin/sa_construct_test: external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/sa_construct_test"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sa_construct_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/build: bin/sa_construct_test
.PHONY : external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/build

external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/sa_construct_test.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/clean

external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/sa_construct_test.dir/depend

