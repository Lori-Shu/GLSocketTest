# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\program\cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\program\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\cppproject\SocketTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\cppproject\SocketTest\build

# Include any dependencies generated for this target.
include src/CMakeFiles/SOCKETTESTClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/SOCKETTESTClient.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/SOCKETTESTClient.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/SOCKETTESTClient.dir/flags.make

src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/flags.make
src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/includes_CXX.rsp
src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj: D:/cppproject/SocketTest/src/ClientApp.cpp
src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\cppproject\SocketTest\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj -MF CMakeFiles\SOCKETTESTClient.dir\ClientApp.cpp.obj.d -o CMakeFiles\SOCKETTESTClient.dir\ClientApp.cpp.obj -c D:\cppproject\SocketTest\src\ClientApp.cpp

src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.i"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\cppproject\SocketTest\src\ClientApp.cpp > CMakeFiles\SOCKETTESTClient.dir\ClientApp.cpp.i

src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.s"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\cppproject\SocketTest\src\ClientApp.cpp -o CMakeFiles\SOCKETTESTClient.dir\ClientApp.cpp.s

src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/flags.make
src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/includes_CXX.rsp
src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj: D:/cppproject/SocketTest/src/GLSocketClient.cpp
src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj: src/CMakeFiles/SOCKETTESTClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\cppproject\SocketTest\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj -MF CMakeFiles\SOCKETTESTClient.dir\GLSocketClient.cpp.obj.d -o CMakeFiles\SOCKETTESTClient.dir\GLSocketClient.cpp.obj -c D:\cppproject\SocketTest\src\GLSocketClient.cpp

src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.i"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\cppproject\SocketTest\src\GLSocketClient.cpp > CMakeFiles\SOCKETTESTClient.dir\GLSocketClient.cpp.i

src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.s"
	cd /d D:\cppproject\SocketTest\build\src && D:\program\MinGWDevKit\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\cppproject\SocketTest\src\GLSocketClient.cpp -o CMakeFiles\SOCKETTESTClient.dir\GLSocketClient.cpp.s

# Object files for target SOCKETTESTClient
SOCKETTESTClient_OBJECTS = \
"CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj" \
"CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj"

# External object files for target SOCKETTESTClient
SOCKETTESTClient_EXTERNAL_OBJECTS =

D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/ClientApp.cpp.obj
D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/GLSocketClient.cpp.obj
D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/build.make
D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/linkLibs.rsp
D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/objects1
D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe: src/CMakeFiles/SOCKETTESTClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\cppproject\SocketTest\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable D:\cppproject\SocketTest\bin\SOCKETTESTClient.exe"
	cd /d D:\cppproject\SocketTest\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SOCKETTESTClient.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/SOCKETTESTClient.dir/build: D:/cppproject/SocketTest/bin/SOCKETTESTClient.exe
.PHONY : src/CMakeFiles/SOCKETTESTClient.dir/build

src/CMakeFiles/SOCKETTESTClient.dir/clean:
	cd /d D:\cppproject\SocketTest\build\src && $(CMAKE_COMMAND) -P CMakeFiles\SOCKETTESTClient.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/SOCKETTESTClient.dir/clean

src/CMakeFiles/SOCKETTESTClient.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\cppproject\SocketTest D:\cppproject\SocketTest\src D:\cppproject\SocketTest\build D:\cppproject\SocketTest\build\src D:\cppproject\SocketTest\build\src\CMakeFiles\SOCKETTESTClient.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SOCKETTESTClient.dir/depend

