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
include CMakeFiles/AsynLogtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AsynLogtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AsynLogtest.dir/flags.make

CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o: CMakeFiles/AsynLogtest.dir/flags.make
CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o: test/base/AsynLogtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o -c /home/lzy/MyChatAppServer/test/base/AsynLogtest.cpp

CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/test/base/AsynLogtest.cpp > CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.i

CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/test/base/AsynLogtest.cpp -o CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.s

# Object files for target AsynLogtest
AsynLogtest_OBJECTS = \
"CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o"

# External object files for target AsynLogtest
AsynLogtest_EXTERNAL_OBJECTS =

bin/AsynLogtest: CMakeFiles/AsynLogtest.dir/test/base/AsynLogtest.cpp.o
bin/AsynLogtest: CMakeFiles/AsynLogtest.dir/build.make
bin/AsynLogtest: libnetlib.a
bin/AsynLogtest: libgtest.a
bin/AsynLogtest: libjsonlib.a
bin/AsynLogtest: CMakeFiles/AsynLogtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/AsynLogtest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AsynLogtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AsynLogtest.dir/build: bin/AsynLogtest

.PHONY : CMakeFiles/AsynLogtest.dir/build

CMakeFiles/AsynLogtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AsynLogtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AsynLogtest.dir/clean

CMakeFiles/AsynLogtest.dir/depend:
	cd /home/lzy/MyChatAppServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer/CMakeFiles/AsynLogtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AsynLogtest.dir/depend
