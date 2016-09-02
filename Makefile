################################################################################
# Name            : Makefile
# Project         : Project
# Description     : Makefile Template
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : jharwell
#
# Note: This file is -j (parallel build) safe, provided you don't mess with it
# too much.
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             bin/BrushWorks           The main executable
#  clean           N/A                      Removes excutable, all .o,
#                                           .preproc files
#  veryclean       N/A                      Everything clean removes, +
#                                           the external libraries and the
#                                           results of ALL analyses.
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# lib/      - Directory where libraries are built, if applicable
# bin/      - Directory where all executables are built
# tests/    - Root directory of all test code for the project
# obj/      - Directory where all object files are built
# lst/      - Direcory where all assembly listing (.lst) files are built
# analysis/ - Root directory for all code analysis that are run

SRCDIR          = ./src
LIBDIR          = ./lib
BINDIR          = ./bin
TESTDIR         = ./tests
OBJDIR          = ./obj
PREPROCDIR      = ./preproc
LSTDIR          = ./lst
ANALYSIS_DIR    = ./analysis
SCANDIR         = $(ANALYSIS_DIR)/scan
EXTDIR          = ./ext
GLUIDIR         = $(EXTDIR)/glui

###############################################################################
# Definitions
###############################################################################

# Tell make we want to execute all commands using bash (otherwise it uses sh)
SHELL           = bash

###############################################################################
# Library Directories
###############################################################################

###############################################################################
# Include Directories
###############################################################################
# Query the gcc-ish compiler and build a list of the system includes. Not
# necessary for compilation (obviously), but needed for some of the analysis
# tools to work.
CXXSYS_INCDIRS := $(addprefix -isystem,$(call inc-query,$(CXX)))

###############################################################################
# C++ Compilation Options
###############################################################################
CXXLIBDIRS ?= -L$(LIBDIR) -L$(GLUIDIR)/lib


# We don't have control over GLUI, so suppress all compiler warnings its
# headers may generate
define CXXINCDIRS
-Iinclude \
-isystem$(GLUIDIR)/include
endef

CXXFLAGS    = $(OPT) -g -D__linux__ -W -Wall -Wextra -Weffc++ -std=gnu++11 -fmessage-length=0 $(CXXINCDIRS)

# In general, note that the order libraries are specified to the linker
# MATTERS. If a library is specified too early on the command line, which can
# happen when:
# 1. It is specified on the command line before the linker processes any
#    source files that contain references to it
# 2. It is specified on the command line with the libraries to link against
#    before another library that contains references to it.
#
# In both these cases the linker will "drop" the library and you will see
# unresolved reference errors.
CXXLIBS     = -lrt -lm -lpthread

# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX
CXXLIBS += -framework glut -framework opengl -lglui
else # LINUX
CXXLIBS += -lglut -lGL -lGLU -lglui
endif

# On some lab machines the glut and opengl libraries are located in the directory
# where the nvidia graphics driver was installed rather than the default /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows up in that dir
ifneq ($(NVIDIA_LIB), )
CXXLIBS += -L$(NVIDIA_LIB)
endif

CXX         = g++
OPT         = -O0

###############################################################################
# Functions
###############################################################################
# Compiler query: Get the list of built in system include directories
# by querying the gcc-ish compiler. Not necessary for compilation
# (obviously), but needed for some of the analysis tools to work.
# usage: $(call inc-query,compiler-name)
#
inc-query=$(shell echo | $(1) -xc -E -v - |& grep  '^ ' |grep include | sed 's/ //g'))

# Recursive wildcard: search a list of directories for all files that match a pattern
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
#
# All directory lists passed as first arg must be separated by spaces, and they
# themselves must be space separated as well. There must NOT be a space between
# the last dir list the , and the start of the pattern.
#
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)  $(filter $(subst *,%,$2),$d))

# make-depend: generate dependencies for C++ source files dynamically. Very useful
# for including .h files as target dependencies.
# usage: $(call make-depend,source-file,object-file,depend-file)
#
# Note that this will not work on files in $(TESTDIR) without modification to
# this makefile.
#
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

define analyze-cppcheck-cmd
cppcheck --enable=all $($(addprefix ANALYZE_SRC_,$1)) $($(addprefix $1,MODULE)) \
$($(addprefix $1,INCDIRS)) $($(addprefix $1,SYS_INCDIRS)) $($(addprefix $1,DEBUG)) \
> $(ANALYSIS_DIR)/cppcheck-analysis-$(shell date --iso=seconds).txt 2>&1
endef

define analyze-clang-syntax-cmd
clang -fsyntax-only -fcolor-diagnostics -Weverything -Wno-undef -Wno-pedantic\
-Wno-padded -Wno-packed -Wno-gnu-zero-variadic-macro-arguments \
$($(addprefix $1,FLAGS)) $($(addprefix $1,SYS_INCDIRS)) \
$($(addprefix ANALYZE_SRC_,$1)) > $(ANALYSIS_DIR)/clang-syntax-analysis-$(shell date --iso=seconds).txt 2>&1
endef

define analyze-clang-static-cmd
clang-check -analyze $($(addprefix ANALYZE_SRC_,$1)) -ast-dump -- $($(addprefix $1,FLAGS)) \
$($(addprefix $1,SYS_INCDIRS)) -fcolor-diagnostics >& \
$(ANALYSIS_DIR)/clang-static-analysis-$(shell date --iso=seconds).txt
endef

###############################################################################
# Target Definitions
###############################################################################
# Define what directories to search for source code
SOURCES    = $(SRCDIR)

# Define the list of files to compile for this project
SRC_CXX    = $(call rwildcard,$(SOURCES),*.cpp)

# Define the list of files to target in an analysis, if one of those targets
# is built. Defaults to all source files (override this on the command line if
# you only want to analyze a smaller number/single file).
ANALYZE_SRC_CXX ?= $(SRC_CXX)

# For each of the .cpp files found above, determine the name of the
# corresponding .o file to create.
OBJECTS_CXX  = $(notdir $(patsubst %.cpp,%.o,$(SRC_CXX)))

# Tell make to search the source and test directories when looking for matches
# in pattern rules. For example, when building obj/foo.o from the pattern rule
# below, make will look ONLY in obj/ for foo.cpp. Adding the source directory
# to the VPATH list fixes this.
VPATH        = $(SRCDIR):$(TESTDIR)

# The target executable (what you are building)
TARGET = $(BINDIR)/BrushWork

# The built-in C tests. My convention is that all tests will end in -test, and
# that all test harness files will end in _test.
TEST_SOURCES = $(TESTDIR)

CXXTEST_SRC = $(notdir $(call rwildcard,$(TEST_SOURCES),*-test.cpp))
CXXTEST_HARNESS = $(strip $(call rwildcard,$(TEST_SOURCES),*_test.cpp))
CXXTESTS = $(patsubst %.cpp,$(BINDIR)/%,$(CXXTEST_SRC))

# Preprocessor output for source code, test code, and test harness. Very
# useful for debugging strange compilation errors, because you can see EXACTLY
# what you are handing to the compiler after all includes and macros are expanded.
define PREPROC_OBJECTS
$(addprefix $(PREPROCDIR)/,$(addsuffix .preproc, $(basename $(notdir $(call rwildcard, $(CXXTEST_SOURCES) $(SOURCES),*.cpp)))))
endef

###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: analyze-c++ analyze-cppcheck-c++ syntax-analyze-clang-c++ static-analyze-clang-c++
.PHONY: analyze-scan clean veryclean scan
.PHONY: glui

# The default target
all: $(TARGET)

# Unless invoked with make clean, include generated dependencies. This makes
# it so that anytime you make an edit in a .h file, all .cpp files that
# include it will automatically be recompiled.
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(OBJECTS_CXX:.o=.d))
endif

# The Target Executable
$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR) $(LSTDIR)
$(TARGET): glui $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) $(CTEST_HARNESS) $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) -o $@ $(CXXLIBS)

# GLUI
glui:
	$(MAKE) -C$(GLUIDIR)

# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(LIBDIR) $(BINDIR)  $(OBJDIR) $(PREPROCDIR) $(LSTDIR) $(ANALYSIS_DIR) $(SCANDIR):
	@mkdir -p $@

# The Helpful Preprocessor
$(PREPROC_OBJECTS): | $(PREPROCDIR)
preprocessor: $(PREPROC_OBJECTS)

# The Cleaner
clean:
	@rm -rf $(LIBDIR) $(BINDIR) $(OBJDIR) $(PREPROCDIR) $(LSTDIR) $(TESTS)

# The Super Cleaner
veryclean: clean
	@rm -rf $(ANALYSIS_DIR)
	@$(MAKE) -C$(GLUIDIR) clean

# The Analyzers
#
# cppcheck     - An analyzer that sometimes reports different things than the
#                clang static checker. Sometimes it reports the same stuff
#                too.
# clang-check  - A very good static analyzer for all types of bugs/ambiguities
# clang-syntax - A VERY verbose set of compiler warnings (way more than
#                gcc/g++), which can be helpful at times.
#
analyze-c++: analyze-cppcheck-c++ analyze-clang-syntax-c++ analyze-clang-static-c++

analyze-cppcheck-c++: | $(ANALYSIS_DIR)
	$(call analyze-cppcheck-cmd,CXX)
analyze-clang-syntax-c++: | $(ANALYSIS_DIR)
	$(call analyze-clang-syntax-cmd,CXX)

analyze-clang-static-c++: | $(ANALYSIS_DIR)
	$(call analyze-clang-static-cmd,CXX)
	@rm -rf *.plist

# The Scanner
#
# Presents the results of the clang static analyzer in a nice GUI/webpage. To
# use this target, you must run 'make clean' first, so scan-build can hook into
# your build process.
analyze-scan: | $(SCANDIR)
	scan-build -V --use-c++=$(CXX) -o $(SCANDIR) -analyze-headers -enable-checker core -enable-checker unix -enable-checker security -enable-checker llvm -enable-checker alpha -disable-checker alpha.core.CastToStruct $(MAKE)

###############################################################################
# Pattern Rules
###############################################################################
# For compiling the C++ source. Specify that any .o file in the object
# directory can be build
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c -o  $@ $<

# For getting preprocessor C++ output
$(PREPROCDIR)/%.preproc:: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXINCDIRS) -E $< -o $@
