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
include CMakeFiles/utillib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/utillib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/utillib.dir/flags.make

CMakeFiles/utillib.dir/utils/StringUtil.cpp.o: CMakeFiles/utillib.dir/flags.make
CMakeFiles/utillib.dir/utils/StringUtil.cpp.o: utils/StringUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/utillib.dir/utils/StringUtil.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utillib.dir/utils/StringUtil.cpp.o -c /home/lzy/MyChatAppServer/utils/StringUtil.cpp

CMakeFiles/utillib.dir/utils/StringUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utillib.dir/utils/StringUtil.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/utils/StringUtil.cpp > CMakeFiles/utillib.dir/utils/StringUtil.cpp.i

CMakeFiles/utillib.dir/utils/StringUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utillib.dir/utils/StringUtil.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/utils/StringUtil.cpp -o CMakeFiles/utillib.dir/utils/StringUtil.cpp.s

CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o: CMakeFiles/utillib.dir/flags.make
CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o: utils/URLEncodeUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o -c /home/lzy/MyChatAppServer/utils/URLEncodeUtil.cpp

CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/utils/URLEncodeUtil.cpp > CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.i

CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/utils/URLEncodeUtil.cpp -o CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.s

CMakeFiles/utillib.dir/utils/MD5.cpp.o: CMakeFiles/utillib.dir/flags.make
CMakeFiles/utillib.dir/utils/MD5.cpp.o: utils/MD5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/utillib.dir/utils/MD5.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utillib.dir/utils/MD5.cpp.o -c /home/lzy/MyChatAppServer/utils/MD5.cpp

CMakeFiles/utillib.dir/utils/MD5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utillib.dir/utils/MD5.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/utils/MD5.cpp > CMakeFiles/utillib.dir/utils/MD5.cpp.i

CMakeFiles/utillib.dir/utils/MD5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utillib.dir/utils/MD5.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/utils/MD5.cpp -o CMakeFiles/utillib.dir/utils/MD5.cpp.s

CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o: CMakeFiles/utillib.dir/flags.make
CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o: utils/DaemonRun.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o -c /home/lzy/MyChatAppServer/utils/DaemonRun.cpp

CMakeFiles/utillib.dir/utils/DaemonRun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utillib.dir/utils/DaemonRun.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/utils/DaemonRun.cpp > CMakeFiles/utillib.dir/utils/DaemonRun.cpp.i

CMakeFiles/utillib.dir/utils/DaemonRun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utillib.dir/utils/DaemonRun.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/utils/DaemonRun.cpp -o CMakeFiles/utillib.dir/utils/DaemonRun.cpp.s

# Object files for target utillib
utillib_OBJECTS = \
"CMakeFiles/utillib.dir/utils/StringUtil.cpp.o" \
"CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o" \
"CMakeFiles/utillib.dir/utils/MD5.cpp.o" \
"CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o"

# External object files for target utillib
utillib_EXTERNAL_OBJECTS =

libutillib.a: CMakeFiles/utillib.dir/utils/StringUtil.cpp.o
libutillib.a: CMakeFiles/utillib.dir/utils/URLEncodeUtil.cpp.o
libutillib.a: CMakeFiles/utillib.dir/utils/MD5.cpp.o
libutillib.a: CMakeFiles/utillib.dir/utils/DaemonRun.cpp.o
libutillib.a: CMakeFiles/utillib.dir/build.make
libutillib.a: CMakeFiles/utillib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libutillib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/utillib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utillib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/utillib.dir/build: libutillib.a

.PHONY : CMakeFiles/utillib.dir/build

CMakeFiles/utillib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/utillib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/utillib.dir/clean

CMakeFiles/utillib.dir/depend:
	cd /home/lzy/MyChatAppServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer/CMakeFiles/utillib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/utillib.dir/depend

