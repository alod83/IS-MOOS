# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.4

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/angelica/Work/temp/SecMOOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/angelica/Work/temp/SecMOOS

# Include any dependencies generated for this target.
include Ex2/CMakeFiles/Ex2.dir/depend.make

# Include the progress variables for this target.
include Ex2/CMakeFiles/Ex2.dir/progress.make

# Include the compile flags for this target's objects.
include Ex2/CMakeFiles/Ex2.dir/flags.make

Ex2/CMakeFiles/Ex2.dir/depend.make.mark: Ex2/CMakeFiles/Ex2.dir/flags.make
Ex2/CMakeFiles/Ex2.dir/depend.make.mark: Ex2/SimpleApp.cpp

Ex2/CMakeFiles/Ex2.dir/SimpleApp.o: Ex2/CMakeFiles/Ex2.dir/flags.make
Ex2/CMakeFiles/Ex2.dir/SimpleApp.o: Ex2/SimpleApp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/angelica/Work/temp/SecMOOS/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Ex2/CMakeFiles/Ex2.dir/SimpleApp.o"
	/usr/bin/c++   $(CXX_FLAGS) -o Ex2/CMakeFiles/Ex2.dir/SimpleApp.o -c /home/angelica/Work/temp/SecMOOS/Ex2/SimpleApp.cpp

Ex2/CMakeFiles/Ex2.dir/SimpleApp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to Ex2/CMakeFiles/Ex2.dir/SimpleApp.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /home/angelica/Work/temp/SecMOOS/Ex2/SimpleApp.cpp > Ex2/CMakeFiles/Ex2.dir/SimpleApp.i

Ex2/CMakeFiles/Ex2.dir/SimpleApp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly Ex2/CMakeFiles/Ex2.dir/SimpleApp.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /home/angelica/Work/temp/SecMOOS/Ex2/SimpleApp.cpp -o Ex2/CMakeFiles/Ex2.dir/SimpleApp.s

Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.requires:

Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.provides: Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.requires
	$(MAKE) -f Ex2/CMakeFiles/Ex2.dir/build.make Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.provides.build

Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.provides.build: Ex2/CMakeFiles/Ex2.dir/SimpleApp.o

Ex2/CMakeFiles/Ex2.dir/depend.make.mark: Ex2/CMakeFiles/Ex2.dir/flags.make
Ex2/CMakeFiles/Ex2.dir/depend.make.mark: Ex2/main.cpp

Ex2/CMakeFiles/Ex2.dir/main.o: Ex2/CMakeFiles/Ex2.dir/flags.make
Ex2/CMakeFiles/Ex2.dir/main.o: Ex2/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/angelica/Work/temp/SecMOOS/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Ex2/CMakeFiles/Ex2.dir/main.o"
	/usr/bin/c++   $(CXX_FLAGS) -o Ex2/CMakeFiles/Ex2.dir/main.o -c /home/angelica/Work/temp/SecMOOS/Ex2/main.cpp

Ex2/CMakeFiles/Ex2.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to Ex2/CMakeFiles/Ex2.dir/main.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /home/angelica/Work/temp/SecMOOS/Ex2/main.cpp > Ex2/CMakeFiles/Ex2.dir/main.i

Ex2/CMakeFiles/Ex2.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly Ex2/CMakeFiles/Ex2.dir/main.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /home/angelica/Work/temp/SecMOOS/Ex2/main.cpp -o Ex2/CMakeFiles/Ex2.dir/main.s

Ex2/CMakeFiles/Ex2.dir/main.o.requires:

Ex2/CMakeFiles/Ex2.dir/main.o.provides: Ex2/CMakeFiles/Ex2.dir/main.o.requires
	$(MAKE) -f Ex2/CMakeFiles/Ex2.dir/build.make Ex2/CMakeFiles/Ex2.dir/main.o.provides.build

Ex2/CMakeFiles/Ex2.dir/main.o.provides.build: Ex2/CMakeFiles/Ex2.dir/main.o

Ex2/CMakeFiles/Ex2.dir/depend: Ex2/CMakeFiles/Ex2.dir/depend.make.mark

Ex2/CMakeFiles/Ex2.dir/depend.make.mark:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --magenta --bold "Scanning dependencies of target Ex2"
	cd /home/angelica/Work/temp/SecMOOS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/angelica/Work/temp/SecMOOS /home/angelica/Work/temp/SecMOOS/Ex2 /home/angelica/Work/temp/SecMOOS /home/angelica/Work/temp/SecMOOS/Ex2 /home/angelica/Work/temp/SecMOOS/Ex2/CMakeFiles/Ex2.dir/DependInfo.cmake

# Object files for target Ex2
Ex2_OBJECTS = \
"CMakeFiles/Ex2.dir/SimpleApp.o" \
"CMakeFiles/Ex2.dir/main.o"

# External object files for target Ex2
Ex2_EXTERNAL_OBJECTS =

MOOSBin/Ex2: Ex2/CMakeFiles/Ex2.dir/SimpleApp.o
MOOSBin/Ex2: Ex2/CMakeFiles/Ex2.dir/main.o
MOOSBin/Ex2: MOOSBin/libMOOSUtility.a
MOOSBin/Ex2: MOOSBin/libMOOS.a
MOOSBin/Ex2: MOOSBin/libMOOSGen.a
MOOSBin/Ex2: Ex2/CMakeFiles/Ex2.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../MOOSBin/Ex2"
	cd /home/angelica/Work/temp/SecMOOS/Ex2 && $(CMAKE_COMMAND) -P CMakeFiles/Ex2.dir/cmake_clean_target.cmake
	cd /home/angelica/Work/temp/SecMOOS/Ex2 && /usr/bin/c++      -fPIC $(Ex2_OBJECTS) $(Ex2_EXTERNAL_OBJECTS)  -o ../MOOSBin/Ex2 -rdynamic -L/home/angelica/Work/temp/SecMOOS/MOOSBin -Wl,-Bstatic -lMOOSUtility -lMOOS -lMOOSGen -Wl,-Bdynamic -lm -lpthread -lssl -Wl,-rpath,/home/angelica/Work/temp/SecMOOS/MOOSBin 

# Rule to build all files generated by this target.
Ex2/CMakeFiles/Ex2.dir/build: MOOSBin/Ex2

Ex2/CMakeFiles/Ex2.dir/requires: Ex2/CMakeFiles/Ex2.dir/SimpleApp.o.requires
Ex2/CMakeFiles/Ex2.dir/requires: Ex2/CMakeFiles/Ex2.dir/main.o.requires

Ex2/CMakeFiles/Ex2.dir/clean:
	cd /home/angelica/Work/temp/SecMOOS/Ex2 && $(CMAKE_COMMAND) -P CMakeFiles/Ex2.dir/cmake_clean.cmake
