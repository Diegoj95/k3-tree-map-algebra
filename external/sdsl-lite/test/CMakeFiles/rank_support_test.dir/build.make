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

# Include any dependencies generated for this target.
include external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/progress.make

# Include the compile flags for this target's objects.
include external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/flags.make

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/flags.make
external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o: external/sdsl-lite/test/rank_support_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o"
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o -c /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/rank_support_test.cpp

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rank_support_test.dir/rank_support_test.cpp.i"
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/rank_support_test.cpp > CMakeFiles/rank_support_test.dir/rank_support_test.cpp.i

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rank_support_test.dir/rank_support_test.cpp.s"
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/rank_support_test.cpp -o CMakeFiles/rank_support_test.dir/rank_support_test.cpp.s

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.requires:
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.requires

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.provides: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.requires
	$(MAKE) -f external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/build.make external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.provides.build
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.provides

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.provides.build: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o

# Object files for target rank_support_test
rank_support_test_OBJECTS = \
"CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o"

# External object files for target rank_support_test
rank_support_test_EXTERNAL_OBJECTS =

external/sdsl-lite/test/rank_support_test: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/build.make
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/lib/libsdsl.a
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/external/googletest/libgtest.a
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/external/libdivsufsort/lib/libdivsufsort.a
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/external/libdivsufsort/lib/libdivsufsort64.a
external/sdsl-lite/test/rank_support_test: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable rank_support_test"
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rank_support_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/build: external/sdsl-lite/test/rank_support_test
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/build

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/requires: external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/rank_support_test.cpp.o.requires
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/requires

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/clean:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/rank_support_test.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/clean

external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/depend:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/sdsl-lite/test/CMakeFiles/rank_support_test.dir/depend

