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
include external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/progress.make

# Include the compile flags for this target's objects.
include external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/flags.make

external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o: external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/flags.make
external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o: /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/replace_int_vector_value.cpp
external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o: external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o -MF CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o.d -o CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o -c /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/replace_int_vector_value.cpp

external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.i"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/replace_int_vector_value.cpp > CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.i

external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.s"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test/replace_int_vector_value.cpp -o CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.s

# Object files for target replace_int_vector_value
replace_int_vector_value_OBJECTS = \
"CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o"

# External object files for target replace_int_vector_value
replace_int_vector_value_EXTERNAL_OBJECTS =

bin/replace_int_vector_value: external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/replace_int_vector_value.cpp.o
bin/replace_int_vector_value: external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/build.make
bin/replace_int_vector_value: lib/libsdsl.a
bin/replace_int_vector_value: lib/libgtest.a
bin/replace_int_vector_value: lib/libdivsufsort.a
bin/replace_int_vector_value: lib/libdivsufsort64.a
bin/replace_int_vector_value: external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/replace_int_vector_value"
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/replace_int_vector_value.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/build: bin/replace_int_vector_value
.PHONY : external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/build

external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/clean:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/replace_int_vector_value.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/clean

external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/depend:
	cd /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test /mnt/44D23BA8D23B9D5C/UBB/Tesis/codigo/otro/k3-tree/build/external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/sdsl-lite/test/CMakeFiles/replace_int_vector_value.dir/depend

