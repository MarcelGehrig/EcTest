# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/mgehrig2/git_repos/EtherCAT/EcTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mgehrig2/git_repos/EtherCAT/EcTest/build

# Include any dependencies generated for this target.
include CMakeFiles/ectest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ectest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ectest.dir/flags.make

CMakeFiles/ectest.dir/main.cpp.o: CMakeFiles/ectest.dir/flags.make
CMakeFiles/ectest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mgehrig2/git_repos/EtherCAT/EcTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ectest.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ectest.dir/main.cpp.o -c /home/mgehrig2/git_repos/EtherCAT/EcTest/main.cpp

CMakeFiles/ectest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ectest.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mgehrig2/git_repos/EtherCAT/EcTest/main.cpp > CMakeFiles/ectest.dir/main.cpp.i

CMakeFiles/ectest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ectest.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mgehrig2/git_repos/EtherCAT/EcTest/main.cpp -o CMakeFiles/ectest.dir/main.cpp.s

CMakeFiles/ectest.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ectest.dir/main.cpp.o.requires

CMakeFiles/ectest.dir/main.cpp.o.provides: CMakeFiles/ectest.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ectest.dir/build.make CMakeFiles/ectest.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ectest.dir/main.cpp.o.provides

CMakeFiles/ectest.dir/main.cpp.o.provides.build: CMakeFiles/ectest.dir/main.cpp.o


# Object files for target ectest
ectest_OBJECTS = \
"CMakeFiles/ectest.dir/main.cpp.o"

# External object files for target ectest
ectest_EXTERNAL_OBJECTS =

ectest: CMakeFiles/ectest.dir/main.cpp.o
ectest: CMakeFiles/ectest.dir/build.make
ectest: CMakeFiles/ectest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mgehrig2/git_repos/EtherCAT/EcTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ectest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ectest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ectest.dir/build: ectest

.PHONY : CMakeFiles/ectest.dir/build

CMakeFiles/ectest.dir/requires: CMakeFiles/ectest.dir/main.cpp.o.requires

.PHONY : CMakeFiles/ectest.dir/requires

CMakeFiles/ectest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ectest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ectest.dir/clean

CMakeFiles/ectest.dir/depend:
	cd /home/mgehrig2/git_repos/EtherCAT/EcTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mgehrig2/git_repos/EtherCAT/EcTest /home/mgehrig2/git_repos/EtherCAT/EcTest /home/mgehrig2/git_repos/EtherCAT/EcTest/build /home/mgehrig2/git_repos/EtherCAT/EcTest/build /home/mgehrig2/git_repos/EtherCAT/EcTest/build/CMakeFiles/ectest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ectest.dir/depend

