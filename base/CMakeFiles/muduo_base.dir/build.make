# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer"

# Include any dependencies generated for this target.
include base/CMakeFiles/muduo_base.dir/depend.make

# Include the progress variables for this target.
include base/CMakeFiles/muduo_base.dir/progress.make

# Include the compile flags for this target's objects.
include base/CMakeFiles/muduo_base.dir/flags.make

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o: base/AsyncLog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/AsyncLog.cpp.o -c "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/AsyncLog.cpp"

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/AsyncLog.cpp.i"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/AsyncLog.cpp" > CMakeFiles/muduo_base.dir/AsyncLog.cpp.i

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/AsyncLog.cpp.s"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/AsyncLog.cpp" -o CMakeFiles/muduo_base.dir/AsyncLog.cpp.s

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.requires:

.PHONY : base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.requires

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.provides: base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.requires
	$(MAKE) -f base/CMakeFiles/muduo_base.dir/build.make base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.provides.build
.PHONY : base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.provides

base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.provides.build: base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o


base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o: base/ConfigFileReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o -c "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/ConfigFileReader.cpp"

base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.i"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/ConfigFileReader.cpp" > CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.i

base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.s"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/ConfigFileReader.cpp" -o CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.s

base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.requires:

.PHONY : base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.requires

base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.provides: base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.requires
	$(MAKE) -f base/CMakeFiles/muduo_base.dir/build.make base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.provides.build
.PHONY : base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.provides

base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.provides.build: base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o


base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o: base/CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o -c "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/CountDownLatch.cpp"

base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/CountDownLatch.cpp" > CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i

base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/CountDownLatch.cpp" -o CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s

base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires:

.PHONY : base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires

base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides: base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires
	$(MAKE) -f base/CMakeFiles/muduo_base.dir/build.make base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides.build
.PHONY : base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides

base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides.build: base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o


base/CMakeFiles/muduo_base.dir/Platform.cpp.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/Platform.cpp.o: base/Platform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object base/CMakeFiles/muduo_base.dir/Platform.cpp.o"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Platform.cpp.o -c "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Platform.cpp"

base/CMakeFiles/muduo_base.dir/Platform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Platform.cpp.i"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Platform.cpp" > CMakeFiles/muduo_base.dir/Platform.cpp.i

base/CMakeFiles/muduo_base.dir/Platform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Platform.cpp.s"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Platform.cpp" -o CMakeFiles/muduo_base.dir/Platform.cpp.s

base/CMakeFiles/muduo_base.dir/Platform.cpp.o.requires:

.PHONY : base/CMakeFiles/muduo_base.dir/Platform.cpp.o.requires

base/CMakeFiles/muduo_base.dir/Platform.cpp.o.provides: base/CMakeFiles/muduo_base.dir/Platform.cpp.o.requires
	$(MAKE) -f base/CMakeFiles/muduo_base.dir/build.make base/CMakeFiles/muduo_base.dir/Platform.cpp.o.provides.build
.PHONY : base/CMakeFiles/muduo_base.dir/Platform.cpp.o.provides

base/CMakeFiles/muduo_base.dir/Platform.cpp.o.provides.build: base/CMakeFiles/muduo_base.dir/Platform.cpp.o


base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o: base/Timestamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Timestamp.cpp.o -c "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Timestamp.cpp"

base/CMakeFiles/muduo_base.dir/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Timestamp.cpp.i"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Timestamp.cpp" > CMakeFiles/muduo_base.dir/Timestamp.cpp.i

base/CMakeFiles/muduo_base.dir/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Timestamp.cpp.s"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/Timestamp.cpp" -o CMakeFiles/muduo_base.dir/Timestamp.cpp.s

base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires:

.PHONY : base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires

base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides: base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires
	$(MAKE) -f base/CMakeFiles/muduo_base.dir/build.make base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides.build
.PHONY : base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides

base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides.build: base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o


# Object files for target muduo_base
muduo_base_OBJECTS = \
"CMakeFiles/muduo_base.dir/AsyncLog.cpp.o" \
"CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o" \
"CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o" \
"CMakeFiles/muduo_base.dir/Platform.cpp.o" \
"CMakeFiles/muduo_base.dir/Timestamp.cpp.o"

# External object files for target muduo_base
muduo_base_EXTERNAL_OBJECTS =

base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/Platform.cpp.o
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/build.make
base/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libmuduo_base.a"
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && $(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean_target.cmake
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
base/CMakeFiles/muduo_base.dir/build: base/libmuduo_base.a

.PHONY : base/CMakeFiles/muduo_base.dir/build

base/CMakeFiles/muduo_base.dir/requires: base/CMakeFiles/muduo_base.dir/AsyncLog.cpp.o.requires
base/CMakeFiles/muduo_base.dir/requires: base/CMakeFiles/muduo_base.dir/ConfigFileReader.cpp.o.requires
base/CMakeFiles/muduo_base.dir/requires: base/CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires
base/CMakeFiles/muduo_base.dir/requires: base/CMakeFiles/muduo_base.dir/Platform.cpp.o.requires
base/CMakeFiles/muduo_base.dir/requires: base/CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires

.PHONY : base/CMakeFiles/muduo_base.dir/requires

base/CMakeFiles/muduo_base.dir/clean:
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" && $(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean.cmake
.PHONY : base/CMakeFiles/muduo_base.dir/clean

base/CMakeFiles/muduo_base.dir/depend:
	cd "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer" "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer" "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base" "/mnt/g/onedrive1/OneDrive - office.ac.id/project_git/MyChatApp/MyChatAppServer/base/CMakeFiles/muduo_base.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : base/CMakeFiles/muduo_base.dir/depend
