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

# Utility rule file for csa-byte-test_zarathustra.txt.

# Include the progress variables for this target.
include external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/progress.make

external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt: external/sdsl-lite/test/test_cases/zarathustra.txt
external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt: external/sdsl-lite/test/tmp
external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt: external/sdsl-lite/test/csa_byte_test
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Execute csa-byte-test on zarathustra.txt."
	/home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/csa_byte_test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/test_cases/zarathustra.txt /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/tmp/csa_byte_test_zarathustra.txt /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/tmp

external/sdsl-lite/test/test_cases/zarathustra.txt:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Checking or downloading test case zarathustra.txt."
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && /usr/bin/cmake -Ddownload_url=http://algo2.iti.kit.edu/gog/sdsl/zarathustra.txt.tar.gz -Dtest_case_dir=/home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/test_cases -P /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/download.cmake

csa-byte-test_zarathustra.txt: external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt
csa-byte-test_zarathustra.txt: external/sdsl-lite/test/test_cases/zarathustra.txt
csa-byte-test_zarathustra.txt: external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/build.make
.PHONY : csa-byte-test_zarathustra.txt

# Rule to build all files generated by this target.
external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/build: csa-byte-test_zarathustra.txt
.PHONY : external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/build

external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/clean:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test && $(CMAKE_COMMAND) -P CMakeFiles/csa-byte-test_zarathustra.txt.dir/cmake_clean.cmake
.PHONY : external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/clean

external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/depend:
	cd /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test /home/fernando/Dropbox/gdrive/Doutoramento/Projects/k3-tree_sdsl/external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/sdsl-lite/test/CMakeFiles/csa-byte-test_zarathustra.txt.dir/depend

