# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lin/GroupKey

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lin/GroupKey/build

# Include any dependencies generated for this target.
include test/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/main.dir/flags.make

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o: ../test/BitCompressedVectorTester.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/BitCompressedVectorTester.cc.o -c /home/lin/GroupKey/test/BitCompressedVectorTester.cc

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/BitCompressedVectorTester.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/test/BitCompressedVectorTester.cc > CMakeFiles/main.dir/BitCompressedVectorTester.cc.i

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/BitCompressedVectorTester.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/test/BitCompressedVectorTester.cc -o CMakeFiles/main.dir/BitCompressedVectorTester.cc.s

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.requires

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.provides: test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.provides

test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.provides.build: test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o

test/CMakeFiles/main.dir/main.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/main.cc.o: ../test/main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/main.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cc.o -c /home/lin/GroupKey/test/main.cc

test/CMakeFiles/main.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/test/main.cc > CMakeFiles/main.dir/main.cc.i

test/CMakeFiles/main.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/test/main.cc -o CMakeFiles/main.dir/main.cc.s

test/CMakeFiles/main.dir/main.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/main.cc.o.requires

test/CMakeFiles/main.dir/main.cc.o.provides: test/CMakeFiles/main.dir/main.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/main.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/main.cc.o.provides

test/CMakeFiles/main.dir/main.cc.o.provides.build: test/CMakeFiles/main.dir/main.cc.o

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o: ../src/BitCompressedVector.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o -c /home/lin/GroupKey/src/BitCompressedVector.cc

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/__/src/BitCompressedVector.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/src/BitCompressedVector.cc > CMakeFiles/main.dir/__/src/BitCompressedVector.cc.i

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/__/src/BitCompressedVector.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/src/BitCompressedVector.cc -o CMakeFiles/main.dir/__/src/BitCompressedVector.cc.s

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.requires

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.provides: test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.provides

test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.provides.build: test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o

test/CMakeFiles/main.dir/__/src/Logging.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/__/src/Logging.cc.o: ../src/Logging.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/__/src/Logging.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/__/src/Logging.cc.o -c /home/lin/GroupKey/src/Logging.cc

test/CMakeFiles/main.dir/__/src/Logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/__/src/Logging.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/src/Logging.cc > CMakeFiles/main.dir/__/src/Logging.cc.i

test/CMakeFiles/main.dir/__/src/Logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/__/src/Logging.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/src/Logging.cc -o CMakeFiles/main.dir/__/src/Logging.cc.s

test/CMakeFiles/main.dir/__/src/Logging.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/__/src/Logging.cc.o.requires

test/CMakeFiles/main.dir/__/src/Logging.cc.o.provides: test/CMakeFiles/main.dir/__/src/Logging.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/__/src/Logging.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/__/src/Logging.cc.o.provides

test/CMakeFiles/main.dir/__/src/Logging.cc.o.provides.build: test/CMakeFiles/main.dir/__/src/Logging.cc.o

test/CMakeFiles/main.dir/__/src/LogStream.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/__/src/LogStream.cc.o: ../src/LogStream.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/__/src/LogStream.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/__/src/LogStream.cc.o -c /home/lin/GroupKey/src/LogStream.cc

test/CMakeFiles/main.dir/__/src/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/__/src/LogStream.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/src/LogStream.cc > CMakeFiles/main.dir/__/src/LogStream.cc.i

test/CMakeFiles/main.dir/__/src/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/__/src/LogStream.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/src/LogStream.cc -o CMakeFiles/main.dir/__/src/LogStream.cc.s

test/CMakeFiles/main.dir/__/src/LogStream.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/__/src/LogStream.cc.o.requires

test/CMakeFiles/main.dir/__/src/LogStream.cc.o.provides: test/CMakeFiles/main.dir/__/src/LogStream.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/__/src/LogStream.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/__/src/LogStream.cc.o.provides

test/CMakeFiles/main.dir/__/src/LogStream.cc.o.provides.build: test/CMakeFiles/main.dir/__/src/LogStream.cc.o

test/CMakeFiles/main.dir/__/src/Timestamp.cc.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/__/src/Timestamp.cc.o: ../src/Timestamp.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lin/GroupKey/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/main.dir/__/src/Timestamp.cc.o"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/__/src/Timestamp.cc.o -c /home/lin/GroupKey/src/Timestamp.cc

test/CMakeFiles/main.dir/__/src/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/__/src/Timestamp.cc.i"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lin/GroupKey/src/Timestamp.cc > CMakeFiles/main.dir/__/src/Timestamp.cc.i

test/CMakeFiles/main.dir/__/src/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/__/src/Timestamp.cc.s"
	cd /home/lin/GroupKey/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lin/GroupKey/src/Timestamp.cc -o CMakeFiles/main.dir/__/src/Timestamp.cc.s

test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.requires:
.PHONY : test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.requires

test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.provides: test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.provides.build
.PHONY : test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.provides

test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.provides.build: test/CMakeFiles/main.dir/__/src/Timestamp.cc.o

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/BitCompressedVectorTester.cc.o" \
"CMakeFiles/main.dir/main.cc.o" \
"CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o" \
"CMakeFiles/main.dir/__/src/Logging.cc.o" \
"CMakeFiles/main.dir/__/src/LogStream.cc.o" \
"CMakeFiles/main.dir/__/src/Timestamp.cc.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

test/main: test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o
test/main: test/CMakeFiles/main.dir/main.cc.o
test/main: test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o
test/main: test/CMakeFiles/main.dir/__/src/Logging.cc.o
test/main: test/CMakeFiles/main.dir/__/src/LogStream.cc.o
test/main: test/CMakeFiles/main.dir/__/src/Timestamp.cc.o
test/main: test/CMakeFiles/main.dir/build.make
test/main: test/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable main"
	cd /home/lin/GroupKey/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/main.dir/build: test/main
.PHONY : test/CMakeFiles/main.dir/build

test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/BitCompressedVectorTester.cc.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/main.cc.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/__/src/BitCompressedVector.cc.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/__/src/Logging.cc.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/__/src/LogStream.cc.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/__/src/Timestamp.cc.o.requires
.PHONY : test/CMakeFiles/main.dir/requires

test/CMakeFiles/main.dir/clean:
	cd /home/lin/GroupKey/build/test && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/main.dir/clean

test/CMakeFiles/main.dir/depend:
	cd /home/lin/GroupKey/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lin/GroupKey /home/lin/GroupKey/test /home/lin/GroupKey/build /home/lin/GroupKey/build/test /home/lin/GroupKey/build/test/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/main.dir/depend

