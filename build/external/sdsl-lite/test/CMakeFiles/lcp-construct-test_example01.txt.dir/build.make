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

# Utility rule file for lcp-construct-test_example01.txt.

# Include any custom commands dependencies for this target.
include external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/progress.make

external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/example01.txt
external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp
external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt: bin/lcp_construct_test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Execute lcp-construct-test on example01.txt."
	/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/bin/lcp_construct_test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/example01.txt /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp/lcp_construct_test_example01.txt /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp

lcp-construct-test_example01.txt: external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt
lcp-construct-test_example01.txt: external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/build.make
.PHONY : lcp-construct-test_example01.txt

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/build: lcp-construct-test_example01.txt
.PHONY : external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/build

external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/lcp-construct-test_example01.txt.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/clean

external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/lcp-construct-test_example01.txt.dir/depend
