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
CMAKE_SOURCE_DIR = /home/lzy/myChatServer/MyChatServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lzy/myChatServer/MyChatServer

# Include any dependencies generated for this target.
include CMakeFiles/mysqllib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mysqllib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mysqllib.dir/flags.make

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o: CMakeFiles/mysqllib.dir/flags.make
CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o: myChatserver/mysqlmgr/MysqlManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/myChatServer/MyChatServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o -c /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlManager.cpp

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlManager.cpp > CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.i

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlManager.cpp -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.s

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o: CMakeFiles/mysqllib.dir/flags.make
CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o: myChatserver/mysqlmgr/MysqlThrd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/myChatServer/MyChatServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o -c /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrd.cpp

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrd.cpp > CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.i

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrd.cpp -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.s

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o: CMakeFiles/mysqllib.dir/flags.make
CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o: myChatserver/mysqlmgr/TaskList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/myChatServer/MyChatServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o -c /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/TaskList.cpp

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/TaskList.cpp > CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.i

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/TaskList.cpp -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.s

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o: CMakeFiles/mysqllib.dir/flags.make
CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o: myChatserver/mysqlmgr/MysqlThrdMgr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/myChatServer/MyChatServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o -c /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrdMgr.cpp

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrdMgr.cpp > CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.i

CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/myChatServer/MyChatServer/myChatserver/mysqlmgr/MysqlThrdMgr.cpp -o CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.s

# Object files for target mysqllib
mysqllib_OBJECTS = \
"CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o" \
"CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o" \
"CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o" \
"CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o"

# External object files for target mysqllib
mysqllib_EXTERNAL_OBJECTS =

libmysqllib.a: CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlManager.cpp.o
libmysqllib.a: CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrd.cpp.o
libmysqllib.a: CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/TaskList.cpp.o
libmysqllib.a: CMakeFiles/mysqllib.dir/myChatserver/mysqlmgr/MysqlThrdMgr.cpp.o
libmysqllib.a: CMakeFiles/mysqllib.dir/build.make
libmysqllib.a: CMakeFiles/mysqllib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/myChatServer/MyChatServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libmysqllib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mysqllib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysqllib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mysqllib.dir/build: libmysqllib.a

.PHONY : CMakeFiles/mysqllib.dir/build

CMakeFiles/mysqllib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mysqllib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mysqllib.dir/clean

CMakeFiles/mysqllib.dir/depend:
	cd /home/lzy/myChatServer/MyChatServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/myChatServer/MyChatServer /home/lzy/myChatServer/MyChatServer /home/lzy/myChatServer/MyChatServer /home/lzy/myChatServer/MyChatServer /home/lzy/myChatServer/MyChatServer/CMakeFiles/mysqllib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mysqllib.dir/depend

