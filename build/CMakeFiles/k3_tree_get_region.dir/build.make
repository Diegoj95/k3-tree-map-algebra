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
include CMakeFiles/k3_tree_get_region.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/k3_tree_get_region.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/k3_tree_get_region.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/k3_tree_get_region.dir/flags.make

CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o: CMakeFiles/k3_tree_get_region.dir/flags.make
CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/k3_tree_get_region.cpp
CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o: CMakeFiles/k3_tree_get_region.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o -MF CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o.d -o CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o -c /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/k3_tree_get_region.cpp

CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/k3_tree_get_region.cpp > CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.i

CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/k3_tree_get_region.cpp -o CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.s

# Object files for target k3_tree_get_region
k3_tree_get_region_OBJECTS = \
"CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o"

# External object files for target k3_tree_get_region
k3_tree_get_region_EXTERNAL_OBJECTS =

bin/k3_tree_get_region: CMakeFiles/k3_tree_get_region.dir/src/k3_tree_get_region.cpp.o
bin/k3_tree_get_region: CMakeFiles/k3_tree_get_region.dir/build.make
bin/k3_tree_get_region: lib/libsdsl.a
bin/k3_tree_get_region: lib/libdivsufsort.a
bin/k3_tree_get_region: lib/libdivsufsort64.a
bin/k3_tree_get_region: lib/liblas.a
bin/k3_tree_get_region: CMakeFiles/k3_tree_get_region.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/k3_tree_get_region"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/k3_tree_get_region.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/k3_tree_get_region.dir/build: bin/k3_tree_get_region
.PHONY : CMakeFiles/k3_tree_get_region.dir/build

CMakeFiles/k3_tree_get_region.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/k3_tree_get_region.dir/cmake_clean.cmake
.PHONY : CMakeFiles/k3_tree_get_region.dir/clean

CMakeFiles/k3_tree_get_region.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles/k3_tree_get_region.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/k3_tree_get_region.dir/depend

