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

# Utility rule file for sa-construct-test_empty.txt.

# Include any custom commands dependencies for this target.
include external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/progress.make

external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/empty.txt
external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp
external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt: bin/sa_construct_test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Execute sa-construct-test on empty.txt."
	/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/bin/sa_construct_test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/test_cases/empty.txt /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp/sa_construct_test_empty.txt /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/tmp

sa-construct-test_empty.txt: external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt
sa-construct-test_empty.txt: external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/build.make
.PHONY : sa-construct-test_empty.txt

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/build: sa-construct-test_empty.txt
.PHONY : external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/build

external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/sa-construct-test_empty.txt.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/clean

external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/sa-construct-test_empty.txt.dir/depend

