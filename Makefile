# List of source files
SOURCES = ./src/fivevar.cpp ./src/fourvar.cpp ./src/grid.cpp ./src/kmapsolver.cpp ./src/main.cpp ./src/threevar.cpp ./src/twovar.cpp ./src/http_request.cpp

# Include directory for your headers
INCLUDE_DIRS_PROJECT = include/
INCLUDE_DIRS_CURL = C:/curl/include

# Library directories for linking
LIB_DIRS_PROJECT = lib/
LIB_DIRS_CURL = C:/curl/lib

# Compiler and linker flags
CXXFLAGS = -g -O1 -Wall -Wno-missing-braces
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcurl

default:
	g++ $(SOURCES) -o kmap.exe my.res $(CXXFLAGS) -I$(INCLUDE_DIRS_CURL) -I$(INCLUDE_DIRS_PROJECT) -L$(LIB_DIRS_CURL) -L$(LIB_DIRS_PROJECT)  $(LDFLAGS) -Wl,--subsystem,windows
	./kmap.exe
