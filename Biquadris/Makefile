# Universal makefile for compiling C++ source files into object files
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#

########## Variables ##########

CXX = g++-11					# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = $(wildcard *.cc) $(wildcard block/*.cc)	# source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}			# object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

########## Targets ##########

all: ${OBJECTS}	

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${DEPENDS}
