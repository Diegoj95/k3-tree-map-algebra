# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl

# Utility rule file for rank-support-test_int-vec.32.1.r.111.

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/progress.make

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/test_cases/int-vec.32.1.r.111
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/tmp
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/rank_support_test
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Execute rank-support-test on int-vec.32.1.r.111."
	/home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/rank_support_test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/test_cases/int-vec.32.1.r.111 /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/tmp/rank_support_test_int-vec.32.1.r.111 /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/tmp

external/sdsl-lite/test/test_cases/int-vec.32.1.r.111: external/sdsl-lite/test/int_vector_generator
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating test case int-vec.32.1.r.111."
	/home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/int_vector_generator /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/test_cases/int-vec.32.1.r.111 32 1 r 111

rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111
rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/test_cases/int-vec.32.1.r.111
rank-support-test_int-vec.32.1.r.111: external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/build.make
.PHONY : rank-support-test_int-vec.32.1.r.111

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/build: rank-support-test_int-vec.32.1.r.111
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/build

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/clean:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/clean

external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/depend:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/sdsl-lite/test/CMakeFiles/rank-support-test_int-vec.32.1.r.111.dir/depend

