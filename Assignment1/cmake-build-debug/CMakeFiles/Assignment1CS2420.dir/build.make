# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Assignment1CS2420.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment1CS2420.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment1CS2420.dir/flags.make

CMakeFiles/Assignment1CS2420.dir/main.cpp.o: CMakeFiles/Assignment1CS2420.dir/flags.make
CMakeFiles/Assignment1CS2420.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Assignment1CS2420.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Assignment1CS2420.dir/main.cpp.o -c /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/main.cpp

CMakeFiles/Assignment1CS2420.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment1CS2420.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/main.cpp > CMakeFiles/Assignment1CS2420.dir/main.cpp.i

CMakeFiles/Assignment1CS2420.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment1CS2420.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/main.cpp -o CMakeFiles/Assignment1CS2420.dir/main.cpp.s

# Object files for target Assignment1CS2420
Assignment1CS2420_OBJECTS = \
"CMakeFiles/Assignment1CS2420.dir/main.cpp.o"

# External object files for target Assignment1CS2420
Assignment1CS2420_EXTERNAL_OBJECTS =

Assignment1CS2420: CMakeFiles/Assignment1CS2420.dir/main.cpp.o
Assignment1CS2420: CMakeFiles/Assignment1CS2420.dir/build.make
Assignment1CS2420: CMakeFiles/Assignment1CS2420.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Assignment1CS2420"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment1CS2420.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment1CS2420.dir/build: Assignment1CS2420

.PHONY : CMakeFiles/Assignment1CS2420.dir/build

CMakeFiles/Assignment1CS2420.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assignment1CS2420.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assignment1CS2420.dir/clean

CMakeFiles/Assignment1CS2420.dir/depend:
	cd /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420 /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420 /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug /Users/masonrich/Desktop/C++/CS2420/Assignment1CS2420/cmake-build-debug/CMakeFiles/Assignment1CS2420.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Assignment1CS2420.dir/depend

