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
include src/bstrlib/CMakeFiles/bstrlib.dir/depend.make

# Include the progress variables for this target.
include src/bstrlib/CMakeFiles/bstrlib.dir/progress.make

# Include the compile flags for this target's objects.
include src/bstrlib/CMakeFiles/bstrlib.dir/flags.make

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o: src/bstrlib/CMakeFiles/bstrlib.dir/flags.make
src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o: ../src/bstrlib/bstrlib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bstrlib.dir/bstrlib.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstrlib.c

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bstrlib.dir/bstrlib.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstrlib.c > CMakeFiles/bstrlib.dir/bstrlib.c.i

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bstrlib.dir/bstrlib.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstrlib.c -o CMakeFiles/bstrlib.dir/bstrlib.c.s

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.requires:
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.requires

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.provides: src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.requires
	$(MAKE) -f src/bstrlib/CMakeFiles/bstrlib.dir/build.make src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.provides.build
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.provides

src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.provides.build: src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o: src/bstrlib/CMakeFiles/bstrlib.dir/flags.make
src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o: ../src/bstrlib/bstraux.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bstrlib.dir/bstraux.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstraux.c

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bstrlib.dir/bstraux.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstraux.c > CMakeFiles/bstrlib.dir/bstraux.c.i

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bstrlib.dir/bstraux.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bstraux.c -o CMakeFiles/bstrlib.dir/bstraux.c.s

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.requires:
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.requires

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.provides: src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.requires
	$(MAKE) -f src/bstrlib/CMakeFiles/bstrlib.dir/build.make src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.provides.build
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.provides

src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.provides.build: src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o: src/bstrlib/CMakeFiles/bstrlib.dir/flags.make
src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o: ../src/bstrlib/bsafe.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/bstrlib.dir/bsafe.c.o   -c /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bsafe.c

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bstrlib.dir/bsafe.c.i"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bsafe.c > CMakeFiles/bstrlib.dir/bsafe.c.i

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bstrlib.dir/bsafe.c.s"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib/bsafe.c -o CMakeFiles/bstrlib.dir/bsafe.c.s

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.requires:
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.requires

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.provides: src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.requires
	$(MAKE) -f src/bstrlib/CMakeFiles/bstrlib.dir/build.make src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.provides.build
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.provides

src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.provides.build: src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o

# Object files for target bstrlib
bstrlib_OBJECTS = \
"CMakeFiles/bstrlib.dir/bstrlib.c.o" \
"CMakeFiles/bstrlib.dir/bstraux.c.o" \
"CMakeFiles/bstrlib.dir/bsafe.c.o"

# External object files for target bstrlib
bstrlib_EXTERNAL_OBJECTS =

src/bstrlib/libbstrlib.a: src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o
src/bstrlib/libbstrlib.a: src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o
src/bstrlib/libbstrlib.a: src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o
src/bstrlib/libbstrlib.a: src/bstrlib/CMakeFiles/bstrlib.dir/build.make
src/bstrlib/libbstrlib.a: src/bstrlib/CMakeFiles/bstrlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libbstrlib.a"
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && $(CMAKE_COMMAND) -P CMakeFiles/bstrlib.dir/cmake_clean_target.cmake
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bstrlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/bstrlib/CMakeFiles/bstrlib.dir/build: src/bstrlib/libbstrlib.a
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/build

src/bstrlib/CMakeFiles/bstrlib.dir/requires: src/bstrlib/CMakeFiles/bstrlib.dir/bstrlib.c.o.requires
src/bstrlib/CMakeFiles/bstrlib.dir/requires: src/bstrlib/CMakeFiles/bstrlib.dir/bstraux.c.o.requires
src/bstrlib/CMakeFiles/bstrlib.dir/requires: src/bstrlib/CMakeFiles/bstrlib.dir/bsafe.c.o.requires
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/requires

src/bstrlib/CMakeFiles/bstrlib.dir/clean:
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib && $(CMAKE_COMMAND) -P CMakeFiles/bstrlib.dir/cmake_clean.cmake
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/clean

src/bstrlib/CMakeFiles/bstrlib.dir/depend:
	cd /home/immo/treehouse/codelite/psy-utils/termtrees/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/immo/treehouse/codelite/psy-utils/termtrees /home/immo/treehouse/codelite/psy-utils/termtrees/src/bstrlib /home/immo/treehouse/codelite/psy-utils/termtrees/Debug /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib /home/immo/treehouse/codelite/psy-utils/termtrees/Debug/src/bstrlib/CMakeFiles/bstrlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bstrlib/CMakeFiles/bstrlib.dir/depend

