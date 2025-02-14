# List of source files
SOURCES = ./src/fivevar.cpp ./src/fourvar.cpp ./src/grid.cpp ./src/kmapsolver.cpp ./src/main.cpp ./src/threevar.cpp ./src/twovar.cpp ./src/http_request.cpp

# List of object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Include directory for your headers
INCLUDE_DIRS_PROJECT = include/
INCLUDE_DIRS_CURL = C:/curl/include
INCLUDE_DIRS_RAYLIB = C:/raylib/raylib/src

# Library directories for linking
LIB_DIRS_PROJECT = lib/
LIB_DIRS_CURL = C:/curl/lib

# Compiler and linker flags
CXXFLAGS = -g -O1 -Wall -Wno-missing-braces -I $(INCLUDE_DIRS_CURL) -I $(INCLUDE_DIRS_PROJECT) -I $(INCLUDE_DIRS_RAYLIB)
LDFLAGS = -L $(LIB_DIRS_CURL) -L $(LIB_DIRS_PROJECT) -lraylib -lopengl32 -lgdi32 -lwinmm -lcurl
REMOVE_TERMINAL_FLAGS = -Wl,--subsystem,windows

# Output executable
TARGET = kmap.exe

# Default target
default: $(TARGET)
	./$(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS)
	g++ $^ -o $@  my.res $(LDFLAGS) $(REMOVE_TERMINAL_FLAGS)

# Compile source files to object files
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)
