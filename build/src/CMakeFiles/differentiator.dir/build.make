# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vboxuser/Documents/expression/Expression

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vboxuser/Documents/expression/Expression/build

# Include any dependencies generated for this target.
include src/CMakeFiles/differentiator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/differentiator.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/differentiator.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/differentiator.dir/flags.make

src/CMakeFiles/differentiator.dir/differentiator.cpp.o: src/CMakeFiles/differentiator.dir/flags.make
src/CMakeFiles/differentiator.dir/differentiator.cpp.o: /home/vboxuser/Documents/expression/Expression/src/differentiator.cpp
src/CMakeFiles/differentiator.dir/differentiator.cpp.o: src/CMakeFiles/differentiator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vboxuser/Documents/expression/Expression/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/differentiator.dir/differentiator.cpp.o"
	cd /home/vboxuser/Documents/expression/Expression/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/differentiator.dir/differentiator.cpp.o -MF CMakeFiles/differentiator.dir/differentiator.cpp.o.d -o CMakeFiles/differentiator.dir/differentiator.cpp.o -c /home/vboxuser/Documents/expression/Expression/src/differentiator.cpp

src/CMakeFiles/differentiator.dir/differentiator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/differentiator.dir/differentiator.cpp.i"
	cd /home/vboxuser/Documents/expression/Expression/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/Documents/expression/Expression/src/differentiator.cpp > CMakeFiles/differentiator.dir/differentiator.cpp.i

src/CMakeFiles/differentiator.dir/differentiator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/differentiator.dir/differentiator.cpp.s"
	cd /home/vboxuser/Documents/expression/Expression/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/Documents/expression/Expression/src/differentiator.cpp -o CMakeFiles/differentiator.dir/differentiator.cpp.s

# Object files for target differentiator
differentiator_OBJECTS = \
"CMakeFiles/differentiator.dir/differentiator.cpp.o"

# External object files for target differentiator
differentiator_EXTERNAL_OBJECTS =

src/differentiator: src/CMakeFiles/differentiator.dir/differentiator.cpp.o
src/differentiator: src/CMakeFiles/differentiator.dir/build.make
src/differentiator: src/libEXPRESSION.a
src/differentiator: src/CMakeFiles/differentiator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/vboxuser/Documents/expression/Expression/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable differentiator"
	cd /home/vboxuser/Documents/expression/Expression/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/differentiator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/differentiator.dir/build: src/differentiator
.PHONY : src/CMakeFiles/differentiator.dir/build

src/CMakeFiles/differentiator.dir/clean:
	cd /home/vboxuser/Documents/expression/Expression/build/src && $(CMAKE_COMMAND) -P CMakeFiles/differentiator.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/differentiator.dir/clean

src/CMakeFiles/differentiator.dir/depend:
	cd /home/vboxuser/Documents/expression/Expression/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vboxuser/Documents/expression/Expression /home/vboxuser/Documents/expression/Expression/src /home/vboxuser/Documents/expression/Expression/build /home/vboxuser/Documents/expression/Expression/build/src /home/vboxuser/Documents/expression/Expression/build/src/CMakeFiles/differentiator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/differentiator.dir/depend

