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
CMAKE_SOURCE_DIR = /home/immo/treehouse/codelite/psy-utils/termtrees

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/immo/treehouse/codelite/psy-utils/termtrees/Debug

# Include any dependencies generated for this target.
include src/CMakeFiles/../termtrees-test.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/../termtrees-test.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/../termtrees-test.dir/flags.make

src/CMakeFiles/../termtrees-test.dir/test.c.o: src/CMakeFiles/../termtrees-test.dir/flags.make
src/CMakeFiles/../termtrees-test.dir/test.c.o: ../src/test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees-test.dir/test.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees-test.dir/test.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/test.c

src/CMakeFiles/../termtrees-test.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees-test.dir/test.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/test.c > CMakeFiles/../termtrees-test.dir/test.c.i

src/CMakeFiles/../termtrees-test.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees-test.dir/test.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/test.c -o CMakeFiles/../termtrees-test.dir/test.c.s

src/CMakeFiles/../termtrees-test.dir/test.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees-test.dir/test.c.o.requires

src/CMakeFiles/../termtrees-test.dir/test.c.o.provides: src/CMakeFiles/../termtrees-test.dir/test.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees-test.dir/build.make src/CMakeFiles/../termtrees-test.dir/test.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees-test.dir/test.c.o.provides

src/CMakeFiles/../termtrees-test.dir/test.c.o.provides.build: src/CMakeFiles/../termtrees-test.dir/test.c.o

src/CMakeFiles/../termtrees-test.dir/op_signature.c.o: src/CMakeFiles/../termtrees-test.dir/flags.make
src/CMakeFiles/../termtrees-test.dir/op_signature.c.o: ../src/op_signature.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees-test.dir/op_signature.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees-test.dir/op_signature.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/op_signature.c

src/CMakeFiles/../termtrees-test.dir/op_signature.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees-test.dir/op_signature.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/op_signature.c > CMakeFiles/../termtrees-test.dir/op_signature.c.i

src/CMakeFiles/../termtrees-test.dir/op_signature.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees-test.dir/op_signature.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/op_signature.c -o CMakeFiles/../termtrees-test.dir/op_signature.c.s

src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.requires

src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.provides: src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees-test.dir/build.make src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.provides

src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.provides.build: src/CMakeFiles/../termtrees-test.dir/op_signature.c.o

src/CMakeFiles/../termtrees-test.dir/cli.c.o: src/CMakeFiles/../termtrees-test.dir/flags.make
src/CMakeFiles/../termtrees-test.dir/cli.c.o: ../src/cli.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees-test.dir/cli.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees-test.dir/cli.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/cli.c

src/CMakeFiles/../termtrees-test.dir/cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees-test.dir/cli.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/cli.c > CMakeFiles/../termtrees-test.dir/cli.c.i

src/CMakeFiles/../termtrees-test.dir/cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees-test.dir/cli.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/cli.c -o CMakeFiles/../termtrees-test.dir/cli.c.s

src/CMakeFiles/../termtrees-test.dir/cli.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees-test.dir/cli.c.o.requires

src/CMakeFiles/../termtrees-test.dir/cli.c.o.provides: src/CMakeFiles/../termtrees-test.dir/cli.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees-test.dir/build.make src/CMakeFiles/../termtrees-test.dir/cli.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees-test.dir/cli.c.o.provides

src/CMakeFiles/../termtrees-test.dir/cli.c.o.provides.build: src/CMakeFiles/../termtrees-test.dir/cli.c.o

src/CMakeFiles/../termtrees-test.dir/terms.c.o: src/CMakeFiles/../termtrees-test.dir/flags.make
src/CMakeFiles/../termtrees-test.dir/terms.c.o: ../src/terms.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees-test.dir/terms.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees-test.dir/terms.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/terms.c

src/CMakeFiles/../termtrees-test.dir/terms.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees-test.dir/terms.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/terms.c > CMakeFiles/../termtrees-test.dir/terms.c.i

src/CMakeFiles/../termtrees-test.dir/terms.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees-test.dir/terms.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/terms.c -o CMakeFiles/../termtrees-test.dir/terms.c.s

src/CMakeFiles/../termtrees-test.dir/terms.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees-test.dir/terms.c.o.requires

src/CMakeFiles/../termtrees-test.dir/terms.c.o.provides: src/CMakeFiles/../termtrees-test.dir/terms.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees-test.dir/build.make src/CMakeFiles/../termtrees-test.dir/terms.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees-test.dir/terms.c.o.provides

src/CMakeFiles/../termtrees-test.dir/terms.c.o.provides.build: src/CMakeFiles/../termtrees-test.dir/terms.c.o

src/CMakeFiles/../termtrees-test.dir/termtrees.c.o: src/CMakeFiles/../termtrees-test.dir/flags.make
src/CMakeFiles/../termtrees-test.dir/termtrees.c.o: ../src/termtrees.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees-test.dir/termtrees.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees-test.dir/termtrees.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/termtrees.c

src/CMakeFiles/../termtrees-test.dir/termtrees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees-test.dir/termtrees.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/termtrees.c > CMakeFiles/../termtrees-test.dir/termtrees.c.i

src/CMakeFiles/../termtrees-test.dir/termtrees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees-test.dir/termtrees.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/termtrees.c -o CMakeFiles/../termtrees-test.dir/termtrees.c.s

src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.requires

src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.provides: src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees-test.dir/build.make src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.provides

src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.provides.build: src/CMakeFiles/../termtrees-test.dir/termtrees.c.o

# Object files for target ../termtrees-test
__/termtrees__test_OBJECTS = \
"CMakeFiles/../termtrees-test.dir/test.c.o" \
"CMakeFiles/../termtrees-test.dir/op_signature.c.o" \
"CMakeFiles/../termtrees-test.dir/cli.c.o" \
"CMakeFiles/../termtrees-test.dir/terms.c.o" \
"CMakeFiles/../termtrees-test.dir/termtrees.c.o"

# External object files for target ../termtrees-test
__/termtrees__test_EXTERNAL_OBJECTS =

src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/test.c.o
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/op_signature.c.o
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/cli.c.o
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/terms.c.o
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/termtrees.c.o
src/../termtrees-test: src/bstrlib/libbstrlib.a
src/../termtrees-test: src/libhygra/libhygra.a
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/build.make
src/../termtrees-test: src/CMakeFiles/../termtrees-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../termtrees-test"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../termtrees-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/../termtrees-test.dir/build: src/../termtrees-test
.PHONY : src/CMakeFiles/../termtrees-test.dir/build

src/CMakeFiles/../termtrees-test.dir/requires: src/CMakeFiles/../termtrees-test.dir/test.c.o.requires
src/CMakeFiles/../termtrees-test.dir/requires: src/CMakeFiles/../termtrees-test.dir/op_signature.c.o.requires
src/CMakeFiles/../termtrees-test.dir/requires: src/CMakeFiles/../termtrees-test.dir/cli.c.o.requires
src/CMakeFiles/../termtrees-test.dir/requires: src/CMakeFiles/../termtrees-test.dir/terms.c.o.requires
src/CMakeFiles/../termtrees-test.dir/requires: src/CMakeFiles/../termtrees-test.dir/termtrees.c.o.requires
.PHONY : src/CMakeFiles/../termtrees-test.dir/requires

src/CMakeFiles/../termtrees-test.dir/clean:
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src && $(CMAKE_COMMAND) -P CMakeFiles/../termtrees-test.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/../termtrees-test.dir/clean

src/CMakeFiles/../termtrees-test.dir/depend:
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/immo/treehouse/codelite/psy-utils/termtrees /home/immo/treehouse/codelite/psy-utils/termtrees/src /home/immo/treehouse/codelite/psy-utils/termtrees/Debug /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/termtrees-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/../termtrees-test.dir/depend

