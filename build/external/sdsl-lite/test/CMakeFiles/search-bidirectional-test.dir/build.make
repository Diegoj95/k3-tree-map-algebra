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

# Utility rule file for search-bidirectional-test.

# Include any custom commands dependencies for this target.
include external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/progress.make

external/sdsl-lite/test/CMakeFiles/search-bidirectional-test:

search-bidirectional-test: external/sdsl-lite/test/CMakeFiles/search-bidirectional-test
search-bidirectional-test: external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/build.make
.PHONY : search-bidirectional-test

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/build: search-bidirectional-test
.PHONY : external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/build

external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/search-bidirectional-test.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/clean

external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/search-bidirectional-test.dir/depend

