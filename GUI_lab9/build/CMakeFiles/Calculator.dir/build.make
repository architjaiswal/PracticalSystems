# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/pi/Desktop/GUI_lab9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/GUI_lab9/build

# Include any dependencies generated for this target.
include CMakeFiles/Calculator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Calculator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Calculator.dir/flags.make

CMakeFiles/Calculator.dir/src/global.cpp.o: CMakeFiles/Calculator.dir/flags.make
CMakeFiles/Calculator.dir/src/global.cpp.o: ../src/global.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/GUI_lab9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Calculator.dir/src/global.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calculator.dir/src/global.cpp.o -c /home/pi/Desktop/GUI_lab9/src/global.cpp

CMakeFiles/Calculator.dir/src/global.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calculator.dir/src/global.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/GUI_lab9/src/global.cpp > CMakeFiles/Calculator.dir/src/global.cpp.i

CMakeFiles/Calculator.dir/src/global.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calculator.dir/src/global.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/GUI_lab9/src/global.cpp -o CMakeFiles/Calculator.dir/src/global.cpp.s

CMakeFiles/Calculator.dir/src/global.cpp.o.requires:

.PHONY : CMakeFiles/Calculator.dir/src/global.cpp.o.requires

CMakeFiles/Calculator.dir/src/global.cpp.o.provides: CMakeFiles/Calculator.dir/src/global.cpp.o.requires
	$(MAKE) -f CMakeFiles/Calculator.dir/build.make CMakeFiles/Calculator.dir/src/global.cpp.o.provides.build
.PHONY : CMakeFiles/Calculator.dir/src/global.cpp.o.provides

CMakeFiles/Calculator.dir/src/global.cpp.o.provides.build: CMakeFiles/Calculator.dir/src/global.cpp.o


CMakeFiles/Calculator.dir/src/main.cpp.o: CMakeFiles/Calculator.dir/flags.make
CMakeFiles/Calculator.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/GUI_lab9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Calculator.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calculator.dir/src/main.cpp.o -c /home/pi/Desktop/GUI_lab9/src/main.cpp

CMakeFiles/Calculator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calculator.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/GUI_lab9/src/main.cpp > CMakeFiles/Calculator.dir/src/main.cpp.i

CMakeFiles/Calculator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calculator.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/GUI_lab9/src/main.cpp -o CMakeFiles/Calculator.dir/src/main.cpp.s

CMakeFiles/Calculator.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/Calculator.dir/src/main.cpp.o.requires

CMakeFiles/Calculator.dir/src/main.cpp.o.provides: CMakeFiles/Calculator.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Calculator.dir/build.make CMakeFiles/Calculator.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Calculator.dir/src/main.cpp.o.provides

CMakeFiles/Calculator.dir/src/main.cpp.o.provides.build: CMakeFiles/Calculator.dir/src/main.cpp.o


# Object files for target Calculator
Calculator_OBJECTS = \
"CMakeFiles/Calculator.dir/src/global.cpp.o" \
"CMakeFiles/Calculator.dir/src/main.cpp.o"

# External object files for target Calculator
Calculator_EXTERNAL_OBJECTS =

Calculator: CMakeFiles/Calculator.dir/src/global.cpp.o
Calculator: CMakeFiles/Calculator.dir/src/main.cpp.o
Calculator: CMakeFiles/Calculator.dir/build.make
Calculator: CMakeFiles/Calculator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/GUI_lab9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Calculator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calculator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Calculator.dir/build: Calculator

.PHONY : CMakeFiles/Calculator.dir/build

CMakeFiles/Calculator.dir/requires: CMakeFiles/Calculator.dir/src/global.cpp.o.requires
CMakeFiles/Calculator.dir/requires: CMakeFiles/Calculator.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/Calculator.dir/requires

CMakeFiles/Calculator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Calculator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Calculator.dir/clean

CMakeFiles/Calculator.dir/depend:
	cd /home/pi/Desktop/GUI_lab9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/GUI_lab9 /home/pi/Desktop/GUI_lab9 /home/pi/Desktop/GUI_lab9/build /home/pi/Desktop/GUI_lab9/build /home/pi/Desktop/GUI_lab9/build/CMakeFiles/Calculator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Calculator.dir/depend
