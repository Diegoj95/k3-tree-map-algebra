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
include CMakeFiles/create_get_region_queries.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/create_get_region_queries.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/create_get_region_queries.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/create_get_region_queries.dir/flags.make

CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o: CMakeFiles/create_get_region_queries.dir/flags.make
CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/test/create_get_region_queries.cpp
CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o: CMakeFiles/create_get_region_queries.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o -MF CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o.d -o CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o -c /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/test/create_get_region_queries.cpp

CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/test/create_get_region_queries.cpp > CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.i

CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/src/test/create_get_region_queries.cpp -o CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.s

# Object files for target create_get_region_queries
create_get_region_queries_OBJECTS = \
"CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o"

# External object files for target create_get_region_queries
create_get_region_queries_EXTERNAL_OBJECTS =

bin/create_get_region_queries: CMakeFiles/create_get_region_queries.dir/src/test/create_get_region_queries.cpp.o
bin/create_get_region_queries: CMakeFiles/create_get_region_queries.dir/build.make
bin/create_get_region_queries: lib/libsdsl.a
bin/create_get_region_queries: lib/libdivsufsort.a
bin/create_get_region_queries: lib/libdivsufsort64.a
bin/create_get_region_queries: lib/liblas.a
bin/create_get_region_queries: CMakeFiles/create_get_region_queries.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/create_get_region_queries"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/create_get_region_queries.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/create_get_region_queries.dir/build: bin/create_get_region_queries
.PHONY : CMakeFiles/create_get_region_queries.dir/build

CMakeFiles/create_get_region_queries.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/create_get_region_queries.dir/cmake_clean.cmake
.PHONY : CMakeFiles/create_get_region_queries.dir/clean

CMakeFiles/create_get_region_queries.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles/create_get_region_queries.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/create_get_region_queries.dir/depend
