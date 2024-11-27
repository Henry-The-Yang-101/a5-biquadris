########## Variables ##########

CXX = g++-11                        # compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD    # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}       # makefile name

SOURCES = $(wildcard *.cc) \
					$(wildcard Biquadris/*.cc) \
					$(wildcard Biquadris/Board/*.cc) \
					$(wildcard Biquadris/Board/Block/*.cc) \
					$(wildcard Biquadris/Board/Level/*.cc) \
					$(wildcard CommandTree/*.cc) \
					$(wildcard CommandTree/BoardActionCommands/*.cc) \
					$(wildcard CommandTree/LevelBlockGenCommands/*.cc) \
					$(wildcard CommandTree/ManageGameStateCommands/*.cc) \
					$(wildcard CommandTree/MetaCommands/*.cc) \
					$(wildcard CommandTree/OutputCommands/*.cc) \
					$(wildcard CommandTree/VisualEffectCommands/*.cc) \
					$(wildcard Displays/*.cc) \
					$(wildcard Miscellaneous/*.cc)

OBJECTS = ${SOURCES:.cc=.o}            # object files forming executable
DEPENDS = ${OBJECTS:.o=.d}            # substitute ".o" with ".d"
EXEC = biquadrisGame                      # executable name

########## Targets ##########

.PHONY: clean                        # not file names

${EXEC}: ${OBJECTS}                   # link step
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11

# Implicit rules to compile .cc to .o files
# Dependencies are generated automatically from the -MMD flag

# Include dependency files if they exist
-include ${DEPENDS}

# Clean up generated files
clean:
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
