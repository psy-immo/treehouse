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
CMAKE_BINARY_DIR = /home/immo/git/treehouse/codelite/psy-utils/termtrees/build

# Include any dependencies generated for this target.
include src/CMakeFiles/../termtrees.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/../termtrees.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/../termtrees.dir/flags.make

src/CMakeFiles/../termtrees.dir/main.c.o: src/CMakeFiles/../termtrees.dir/flags.make
src/CMakeFiles/../termtrees.dir/main.c.o: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees.dir/main.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees.dir/main.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/main.c

src/CMakeFiles/../termtrees.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees.dir/main.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/main.c > CMakeFiles/../termtrees.dir/main.c.i

src/CMakeFiles/../termtrees.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees.dir/main.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/main.c -o CMakeFiles/../termtrees.dir/main.c.s

src/CMakeFiles/../termtrees.dir/main.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees.dir/main.c.o.requires

src/CMakeFiles/../termtrees.dir/main.c.o.provides: src/CMakeFiles/../termtrees.dir/main.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees.dir/build.make src/CMakeFiles/../termtrees.dir/main.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees.dir/main.c.o.provides

src/CMakeFiles/../termtrees.dir/main.c.o.provides.build: src/CMakeFiles/../termtrees.dir/main.c.o

src/CMakeFiles/../termtrees.dir/op_signature.c.o: src/CMakeFiles/../termtrees.dir/flags.make
src/CMakeFiles/../termtrees.dir/op_signature.c.o: ../src/op_signature.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees.dir/op_signature.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees.dir/op_signature.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/op_signature.c

src/CMakeFiles/../termtrees.dir/op_signature.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees.dir/op_signature.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/op_signature.c > CMakeFiles/../termtrees.dir/op_signature.c.i

src/CMakeFiles/../termtrees.dir/op_signature.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees.dir/op_signature.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/op_signature.c -o CMakeFiles/../termtrees.dir/op_signature.c.s

src/CMakeFiles/../termtrees.dir/op_signature.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees.dir/op_signature.c.o.requires

src/CMakeFiles/../termtrees.dir/op_signature.c.o.provides: src/CMakeFiles/../termtrees.dir/op_signature.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees.dir/build.make src/CMakeFiles/../termtrees.dir/op_signature.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees.dir/op_signature.c.o.provides

src/CMakeFiles/../termtrees.dir/op_signature.c.o.provides.build: src/CMakeFiles/../termtrees.dir/op_signature.c.o

src/CMakeFiles/../termtrees.dir/cli.c.o: src/CMakeFiles/../termtrees.dir/flags.make
src/CMakeFiles/../termtrees.dir/cli.c.o: ../src/cli.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees.dir/cli.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees.dir/cli.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/cli.c

src/CMakeFiles/../termtrees.dir/cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees.dir/cli.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/cli.c > CMakeFiles/../termtrees.dir/cli.c.i

src/CMakeFiles/../termtrees.dir/cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees.dir/cli.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/cli.c -o CMakeFiles/../termtrees.dir/cli.c.s

src/CMakeFiles/../termtrees.dir/cli.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees.dir/cli.c.o.requires

src/CMakeFiles/../termtrees.dir/cli.c.o.provides: src/CMakeFiles/../termtrees.dir/cli.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees.dir/build.make src/CMakeFiles/../termtrees.dir/cli.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees.dir/cli.c.o.provides

src/CMakeFiles/../termtrees.dir/cli.c.o.provides.build: src/CMakeFiles/../termtrees.dir/cli.c.o

src/CMakeFiles/../termtrees.dir/terms.c.o: src/CMakeFiles/../termtrees.dir/flags.make
src/CMakeFiles/../termtrees.dir/terms.c.o: ../src/terms.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees.dir/terms.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees.dir/terms.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/terms.c

src/CMakeFiles/../termtrees.dir/terms.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees.dir/terms.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/terms.c > CMakeFiles/../termtrees.dir/terms.c.i

src/CMakeFiles/../termtrees.dir/terms.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees.dir/terms.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/terms.c -o CMakeFiles/../termtrees.dir/terms.c.s

src/CMakeFiles/../termtrees.dir/terms.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees.dir/terms.c.o.requires

src/CMakeFiles/../termtrees.dir/terms.c.o.provides: src/CMakeFiles/../termtrees.dir/terms.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees.dir/build.make src/CMakeFiles/../termtrees.dir/terms.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees.dir/terms.c.o.provides

src/CMakeFiles/../termtrees.dir/terms.c.o.provides.build: src/CMakeFiles/../termtrees.dir/terms.c.o

src/CMakeFiles/../termtrees.dir/termtrees.c.o: src/CMakeFiles/../termtrees.dir/flags.make
src/CMakeFiles/../termtrees.dir/termtrees.c.o: ../src/termtrees.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/../termtrees.dir/termtrees.c.o"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/../termtrees.dir/termtrees.c.o   -c /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/termtrees.c

src/CMakeFiles/../termtrees.dir/termtrees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../termtrees.dir/termtrees.c.i"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/termtrees.c > CMakeFiles/../termtrees.dir/termtrees.c.i

src/CMakeFiles/../termtrees.dir/termtrees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../termtrees.dir/termtrees.c.s"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/git/treehouse/codelite/psy-utils/termtrees/src/termtrees.c -o CMakeFiles/../termtrees.dir/termtrees.c.s

src/CMakeFiles/../termtrees.dir/termtrees.c.o.requires:
.PHONY : src/CMakeFiles/../termtrees.dir/termtrees.c.o.requires

src/CMakeFiles/../termtrees.dir/termtrees.c.o.provides: src/CMakeFiles/../termtrees.dir/termtrees.c.o.requires
	$(MAKE) -f src/CMakeFiles/../termtrees.dir/build.make src/CMakeFiles/../termtrees.dir/termtrees.c.o.provides.build
.PHONY : src/CMakeFiles/../termtrees.dir/termtrees.c.o.provides

src/CMakeFiles/../termtrees.dir/termtrees.c.o.provides.build: src/CMakeFiles/../termtrees.dir/termtrees.c.o

# Object files for target ../termtrees
__/termtrees_OBJECTS = \
"CMakeFiles/../termtrees.dir/main.c.o" \
"CMakeFiles/../termtrees.dir/op_signature.c.o" \
"CMakeFiles/../termtrees.dir/cli.c.o" \
"CMakeFiles/../termtrees.dir/terms.c.o" \
"CMakeFiles/../termtrees.dir/termtrees.c.o"

# External object files for target ../termtrees
__/termtrees_EXTERNAL_OBJECTS =

src/../termtrees: src/CMakeFiles/../termtrees.dir/main.c.o
src/../termtrees: src/CMakeFiles/../termtrees.dir/op_signature.c.o
src/../termtrees: src/CMakeFiles/../termtrees.dir/cli.c.o
src/../termtrees: src/CMakeFiles/../termtrees.dir/terms.c.o
src/../termtrees: src/CMakeFiles/../termtrees.dir/termtrees.c.o
src/../termtrees: src/bstrlib/libbstrlib.a
src/../termtrees: src/CMakeFiles/../termtrees.dir/build.make
src/../termtrees: src/CMakeFiles/../termtrees.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../termtrees"
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../termtrees.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/../termtrees.dir/build: src/../termtrees
.PHONY : src/CMakeFiles/../termtrees.dir/build

src/CMakeFiles/../termtrees.dir/requires: src/CMakeFiles/../termtrees.dir/main.c.o.requires
src/CMakeFiles/../termtrees.dir/requires: src/CMakeFiles/../termtrees.dir/op_signature.c.o.requires
src/CMakeFiles/../termtrees.dir/requires: src/CMakeFiles/../termtrees.dir/cli.c.o.requires
src/CMakeFiles/../termtrees.dir/requires: src/CMakeFiles/../termtrees.dir/terms.c.o.requires
src/CMakeFiles/../termtrees.dir/requires: src/CMakeFiles/../termtrees.dir/termtrees.c.o.requires
.PHONY : src/CMakeFiles/../termtrees.dir/requires

src/CMakeFiles/../termtrees.dir/clean:
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src && $(CMAKE_COMMAND) -P CMakeFiles/../termtrees.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/../termtrees.dir/clean

src/CMakeFiles/../termtrees.dir/depend:
	cd /home/immo/git/treehouse/codelite/psy-utils/termtrees/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/immo/git/treehouse/codelite/psy-utils/termtrees /home/immo/git/treehouse/codelite/psy-utils/termtrees/src /home/immo/git/treehouse/codelite/psy-utils/termtrees/build /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src /home/immo/git/treehouse/codelite/psy-utils/termtrees/build/src/termtrees.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/../termtrees.dir/depend

