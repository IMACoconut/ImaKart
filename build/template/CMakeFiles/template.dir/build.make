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
CMAKE_SOURCE_DIR = /home/andre/Documents/Projects/ImaKart

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andre/Documents/Projects/ImaKart/build

# Include any dependencies generated for this target.
include template/CMakeFiles/template.dir/depend.make

# Include the progress variables for this target.
include template/CMakeFiles/template.dir/progress.make

# Include the compile flags for this target's objects.
include template/CMakeFiles/template.dir/flags.make

template/CMakeFiles/template.dir/main.cpp.o: template/CMakeFiles/template.dir/flags.make
template/CMakeFiles/template.dir/main.cpp.o: ../template/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/Documents/Projects/ImaKart/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object template/CMakeFiles/template.dir/main.cpp.o"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/template.dir/main.cpp.o -c /home/andre/Documents/Projects/ImaKart/template/main.cpp

template/CMakeFiles/template.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template.dir/main.cpp.i"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/Documents/Projects/ImaKart/template/main.cpp > CMakeFiles/template.dir/main.cpp.i

template/CMakeFiles/template.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template.dir/main.cpp.s"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/Documents/Projects/ImaKart/template/main.cpp -o CMakeFiles/template.dir/main.cpp.s

template/CMakeFiles/template.dir/main.cpp.o.requires:
.PHONY : template/CMakeFiles/template.dir/main.cpp.o.requires

template/CMakeFiles/template.dir/main.cpp.o.provides: template/CMakeFiles/template.dir/main.cpp.o.requires
	$(MAKE) -f template/CMakeFiles/template.dir/build.make template/CMakeFiles/template.dir/main.cpp.o.provides.build
.PHONY : template/CMakeFiles/template.dir/main.cpp.o.provides

template/CMakeFiles/template.dir/main.cpp.o.provides.build: template/CMakeFiles/template.dir/main.cpp.o

template/CMakeFiles/template.dir/Game/Entity.cpp.o: template/CMakeFiles/template.dir/flags.make
template/CMakeFiles/template.dir/Game/Entity.cpp.o: ../template/Game/Entity.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/Documents/Projects/ImaKart/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object template/CMakeFiles/template.dir/Game/Entity.cpp.o"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/template.dir/Game/Entity.cpp.o -c /home/andre/Documents/Projects/ImaKart/template/Game/Entity.cpp

template/CMakeFiles/template.dir/Game/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template.dir/Game/Entity.cpp.i"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/Documents/Projects/ImaKart/template/Game/Entity.cpp > CMakeFiles/template.dir/Game/Entity.cpp.i

template/CMakeFiles/template.dir/Game/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template.dir/Game/Entity.cpp.s"
	cd /home/andre/Documents/Projects/ImaKart/build/template && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/Documents/Projects/ImaKart/template/Game/Entity.cpp -o CMakeFiles/template.dir/Game/Entity.cpp.s

template/CMakeFiles/template.dir/Game/Entity.cpp.o.requires:
.PHONY : template/CMakeFiles/template.dir/Game/Entity.cpp.o.requires

template/CMakeFiles/template.dir/Game/Entity.cpp.o.provides: template/CMakeFiles/template.dir/Game/Entity.cpp.o.requires
	$(MAKE) -f template/CMakeFiles/template.dir/build.make template/CMakeFiles/template.dir/Game/Entity.cpp.o.provides.build
.PHONY : template/CMakeFiles/template.dir/Game/Entity.cpp.o.provides

template/CMakeFiles/template.dir/Game/Entity.cpp.o.provides.build: template/CMakeFiles/template.dir/Game/Entity.cpp.o

# Object files for target template
template_OBJECTS = \
"CMakeFiles/template.dir/main.cpp.o" \
"CMakeFiles/template.dir/Game/Entity.cpp.o"

# External object files for target template
template_EXTERNAL_OBJECTS =

template/template: template/CMakeFiles/template.dir/main.cpp.o
template/template: template/CMakeFiles/template.dir/Game/Entity.cpp.o
template/template: template/CMakeFiles/template.dir/build.make
template/template: third-party/glew-1.10.0/libglew.a
template/template: /usr/lib/x86_64-linux-gnu/libGLU.so
template/template: /usr/lib/x86_64-linux-gnu/libGL.so
template/template: /usr/lib/x86_64-linux-gnu/libX11.so
template/template: /usr/lib/x86_64-linux-gnu/libXext.so
template/template: third-party/SFML-2.1/lib/libsfml-graphics.so.2.1
template/template: third-party/SFML-2.1/lib/libsfml-window.so.2.1
template/template: third-party/SFML-2.1/lib/libsfml-system.so.2.1
template/template: lib/libimacoconut.so
template/template: /usr/lib/x86_64-linux-gnu/libXrandr.so
template/template: /usr/lib/x86_64-linux-gnu/libfreetype.so
template/template: /usr/lib/x86_64-linux-gnu/libGLEW.so
template/template: /usr/lib/x86_64-linux-gnu/libjpeg.so
template/template: /usr/lib/x86_64-linux-gnu/libGL.so
template/template: /usr/lib/x86_64-linux-gnu/libX11.so
template/template: /usr/lib/x86_64-linux-gnu/libXext.so
template/template: template/CMakeFiles/template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable template"
	cd /home/andre/Documents/Projects/ImaKart/build/template && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
template/CMakeFiles/template.dir/build: template/template
.PHONY : template/CMakeFiles/template.dir/build

template/CMakeFiles/template.dir/requires: template/CMakeFiles/template.dir/main.cpp.o.requires
template/CMakeFiles/template.dir/requires: template/CMakeFiles/template.dir/Game/Entity.cpp.o.requires
.PHONY : template/CMakeFiles/template.dir/requires

template/CMakeFiles/template.dir/clean:
	cd /home/andre/Documents/Projects/ImaKart/build/template && $(CMAKE_COMMAND) -P CMakeFiles/template.dir/cmake_clean.cmake
.PHONY : template/CMakeFiles/template.dir/clean

template/CMakeFiles/template.dir/depend:
	cd /home/andre/Documents/Projects/ImaKart/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andre/Documents/Projects/ImaKart /home/andre/Documents/Projects/ImaKart/template /home/andre/Documents/Projects/ImaKart/build /home/andre/Documents/Projects/ImaKart/build/template /home/andre/Documents/Projects/ImaKart/build/template/CMakeFiles/template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : template/CMakeFiles/template.dir/depend

