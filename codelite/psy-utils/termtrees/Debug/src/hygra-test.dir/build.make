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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/immo/git/treehouse/codelite/psy-utils/termtrees

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug

# Include any dependencies generated for this target.
include src/libhygra/CMakeFiles/../../hygra-test.dir/depend.make

# Include the progress variables for this target.
include src/libhygra/CMakeFiles/../../hygra-test.dir/progress.make

# Include the compile flags for this target's objects.
include src/libhygra/CMakeFiles/../../hygra-test.dir/flags.make

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o: src/libhygra/CMakeFiles/../../hygra-test.dir/flags.make
src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o: ../src/libhygra/test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../../hygra-test.dir/test.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/libhygra/test.c

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../../hygra-test.dir/test.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/libhygra/test.c > CMakeFiles/../../hygra-test.dir/test.c.i

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../../hygra-test.dir/test.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/libhygra/test.c -o CMakeFiles/../../hygra-test.dir/test.c.s

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.requires:
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.requires

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.provides: src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.requires
	$(MAKE) -f src/libhygra/CMakeFiles/../../hygra-test.dir/build.make src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.provides.build
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.provides

src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.provides.build: src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o

# Object files for target ../../hygra-test
__/__/hygra__test_OBJECTS = \
"CMakeFiles/../../hygra-test.dir/test.c.o"

# External object files for target ../../hygra-test
__/__/hygra__test_EXTERNAL_OBJECTS =

src/libhygra/../../hygra-test: src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o
src/libhygra/../../hygra-test: src/bstrlib/libbstrlib.a
src/libhygra/../../hygra-test: src/libhygra/libhygra.a
src/libhygra/../../hygra-test: src/libhygra/CMakeFiles/../../hygra-test.dir/build.make
src/libhygra/../../hygra-test: src/libhygra/CMakeFiles/../../hygra-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../hygra-test"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../../hygra-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libhygra/CMakeFiles/../../hygra-test.dir/build: src/libhygra/../../hygra-test
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/build

src/libhygra/CMakeFiles/../../hygra-test.dir/requires: src/libhygra/CMakeFiles/../../hygra-test.dir/test.c.o.requires
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/requires

src/libhygra/CMakeFiles/../../hygra-test.dir/clean:
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra && $(CMAKE_COMMAND) -P CMakeFiles/../../hygra-test.dir/cmake_clean.cmake
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/clean

src/libhygra/CMakeFiles/../../hygra-test.dir/depend:
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/immo/git/treehouse/codelite/psy-utils/termtrees /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/libhygra /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/libhygra /home/immo/git/treehouse/codelite/psy-utils/termtrees/Debug/src/hygra-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libhygra/CMakeFiles/../../hygra-test.dir/depend

