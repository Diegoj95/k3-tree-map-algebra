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

# Utility rule file for rank-support-test_int-vec.13.1.1.

# Include any custom commands dependencies for this target.
include external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/progress.make

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/int-vec.13.1.1
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1: bin/rank_support_test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Execute rank-support-test on int-vec.13.1.1."
	/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/bin/rank_support_test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/int-vec.13.1.1 /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp/rank_support_test_int-vec.13.1.1 /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp

/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/int-vec.13.1.1: bin/int_vector_generator
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating test case int-vec.13.1.1."
	/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/bin/int_vector_generator /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/int-vec.13.1.1 13 1 1

rank-support-test_int-vec.13.1.1: external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1
rank-support-test_int-vec.13.1.1: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/int-vec.13.1.1
rank-support-test_int-vec.13.1.1: external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/build.make
.PHONY : rank-support-test_int-vec.13.1.1

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/build: rank-support-test_int-vec.13.1.1
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/build

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/rank-support-test_int-vec.13.1.1.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/clean

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.13.1.1.dir/depend

