# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/program2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/program2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program2.dir/flags.make

CMakeFiles/program2.dir/main.cpp.obj: CMakeFiles/program2.dir/flags.make
CMakeFiles/program2.dir/main.cpp.obj: CMakeFiles/program2.dir/includes_CXX.rsp
CMakeFiles/program2.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/program2.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\program2.dir\main.cpp.obj -c C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\main.cpp

CMakeFiles/program2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/program2.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\main.cpp > CMakeFiles\program2.dir\main.cpp.i

CMakeFiles/program2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/program2.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\main.cpp -o CMakeFiles\program2.dir\main.cpp.s

CMakeFiles/program2.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/program2.dir/main.cpp.obj.requires

CMakeFiles/program2.dir/main.cpp.obj.provides: CMakeFiles/program2.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\program2.dir\build.make CMakeFiles/program2.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/program2.dir/main.cpp.obj.provides

CMakeFiles/program2.dir/main.cpp.obj.provides.build: CMakeFiles/program2.dir/main.cpp.obj


CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj: CMakeFiles/program2.dir/flags.make
CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj: CMakeFiles/program2.dir/includes_C.rsp
CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj: C:/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\program2.dir\C_\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c.obj   -c C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c

CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c > CMakeFiles\program2.dir\C_\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c.i

CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c -o CMakeFiles\program2.dir\C_\Users\gross\Documents\GitHub\csci441-spring2018\programs\lib\glad\src\glad.c.s

CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.requires:

.PHONY : CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.requires

CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.provides: CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.requires
	$(MAKE) -f CMakeFiles\program2.dir\build.make CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.provides.build
.PHONY : CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.provides

CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.provides.build: CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj


# Object files for target program2
program2_OBJECTS = \
"CMakeFiles/program2.dir/main.cpp.obj" \
"CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj"

# External object files for target program2
program2_EXTERNAL_OBJECTS =

program2.exe: CMakeFiles/program2.dir/main.cpp.obj
program2.exe: CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj
program2.exe: CMakeFiles/program2.dir/build.make
program2.exe: glfw/src/libglfw3.a
program2.exe: CMakeFiles/program2.dir/linklibs.rsp
program2.exe: CMakeFiles/program2.dir/objects1.rsp
program2.exe: CMakeFiles/program2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable program2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\program2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program2.dir/build: program2.exe

.PHONY : CMakeFiles/program2.dir/build

CMakeFiles/program2.dir/requires: CMakeFiles/program2.dir/main.cpp.obj.requires
CMakeFiles/program2.dir/requires: CMakeFiles/program2.dir/C_/Users/gross/Documents/GitHub/csci441-spring2018/programs/lib/glad/src/glad.c.obj.requires

.PHONY : CMakeFiles/program2.dir/requires

CMakeFiles/program2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\program2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/program2.dir/clean

CMakeFiles/program2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2 C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2 C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug C:\Users\gross\Documents\GitHub\csci441-spring2018\programs\program2\cmake-build-debug\CMakeFiles\program2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/program2.dir/depend

