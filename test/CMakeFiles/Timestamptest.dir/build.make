# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/lzy/Downloads/clion-2019.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lzy/Downloads/clion-2019.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lzy/MyChatAppServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lzy/MyChatAppServer

# Include any dependencies generated for this target.
include test/CMakeFiles/Timestamptest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/Timestamptest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/Timestamptest.dir/flags.make

test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o: test/CMakeFiles/Timestamptest.dir/flags.make
test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o: test/base/Timestamptest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o"
	cd /home/lzy/MyChatAppServer/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o -c /home/lzy/MyChatAppServer/test/base/Timestamptest.cpp

test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.i"
	cd /home/lzy/MyChatAppServer/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/test/base/Timestamptest.cpp > CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.i

test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.s"
	cd /home/lzy/MyChatAppServer/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/test/base/Timestamptest.cpp -o CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.s

# Object files for target Timestamptest
Timestamptest_OBJECTS = \
"CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o"

# External object files for target Timestamptest
Timestamptest_EXTERNAL_OBJECTS =

test/Timestamptest: test/CMakeFiles/Timestamptest.dir/base/Timestamptest.cpp.o
test/Timestamptest: test/CMakeFiles/Timestamptest.dir/build.make
test/Timestamptest: test/libgtest.a
test/Timestamptest: test/CMakeFiles/Timestamptest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Timestamptest"
	cd /home/lzy/MyChatAppServer/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Timestamptest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/Timestamptest.dir/build: test/Timestamptest

.PHONY : test/CMakeFiles/Timestamptest.dir/build

test/CMakeFiles/Timestamptest.dir/clean:
	cd /home/lzy/MyChatAppServer/test && $(CMAKE_COMMAND) -P CMakeFiles/Timestamptest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/Timestamptest.dir/clean

test/CMakeFiles/Timestamptest.dir/depend:
	cd /home/lzy/MyChatAppServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer/test /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer/test /home/lzy/MyChatAppServer/test/CMakeFiles/Timestamptest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/Timestamptest.dir/depend

