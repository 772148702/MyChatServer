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
include CMakeFiles/mychat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mychat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mychat.dir/flags.make

CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o: CMakeFiles/mychat.dir/flags.make
CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o: myChatserver/chatserversrc/UserManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o -c /home/lzy/MyChatAppServer/myChatserver/chatserversrc/UserManager.cpp

CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/myChatserver/chatserversrc/UserManager.cpp > CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.i

CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/myChatserver/chatserversrc/UserManager.cpp -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.s

CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o: CMakeFiles/mychat.dir/flags.make
CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o: myChatserver/chatserversrc/MsgCacheManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o -c /home/lzy/MyChatAppServer/myChatserver/chatserversrc/MsgCacheManager.cpp

CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/myChatserver/chatserversrc/MsgCacheManager.cpp > CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.i

CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/myChatserver/chatserversrc/MsgCacheManager.cpp -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.s

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o: CMakeFiles/mychat.dir/flags.make
CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o: myChatserver/chatserversrc/ChatSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o -c /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatSession.cpp

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatSession.cpp > CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.i

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatSession.cpp -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.s

CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o: CMakeFiles/mychat.dir/flags.make
CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o: myChatserver/chatserversrc/TcpSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o -c /home/lzy/MyChatAppServer/myChatserver/chatserversrc/TcpSession.cpp

CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/myChatserver/chatserversrc/TcpSession.cpp > CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.i

CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/myChatserver/chatserversrc/TcpSession.cpp -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.s

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o: CMakeFiles/mychat.dir/flags.make
CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o: myChatserver/chatserversrc/ChatServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o -c /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatServer.cpp

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatServer.cpp > CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.i

CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lzy/MyChatAppServer/myChatserver/chatserversrc/ChatServer.cpp -o CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.s

# Object files for target mychat
mychat_OBJECTS = \
"CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o" \
"CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o" \
"CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o" \
"CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o" \
"CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o"

# External object files for target mychat
mychat_EXTERNAL_OBJECTS =

libmychat.a: CMakeFiles/mychat.dir/myChatserver/chatserversrc/UserManager.cpp.o
libmychat.a: CMakeFiles/mychat.dir/myChatserver/chatserversrc/MsgCacheManager.cpp.o
libmychat.a: CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatSession.cpp.o
libmychat.a: CMakeFiles/mychat.dir/myChatserver/chatserversrc/TcpSession.cpp.o
libmychat.a: CMakeFiles/mychat.dir/myChatserver/chatserversrc/ChatServer.cpp.o
libmychat.a: CMakeFiles/mychat.dir/build.make
libmychat.a: CMakeFiles/mychat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/MyChatAppServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libmychat.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mychat.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mychat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mychat.dir/build: libmychat.a

.PHONY : CMakeFiles/mychat.dir/build

CMakeFiles/mychat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mychat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mychat.dir/clean

CMakeFiles/mychat.dir/depend:
	cd /home/lzy/MyChatAppServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer /home/lzy/MyChatAppServer/CMakeFiles/mychat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mychat.dir/depend

