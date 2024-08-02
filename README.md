# Karnaugh Map (K-Map) Solver in C++

This project contains a robust and efficient KMap Solver developed in C++. The project utilizes the Raylib library to provide a visually appealing and user-friendly graphical interface, making it easy to input, manipulate, and visualize Karnaugh maps.

## Table of Contents

- [Tutorial](#tutorial)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Tutorial
![tutorial.gif](./assets/tutorial.gif?raw=true)

## Features
-  Interactive K-Map Grid
-  Calculation of MinTerms
-  Supported upto 5 variables
-  Simplification of Boolean Expressions

## Installation

1. **Install Dependencies**:

   Ensure you have installed all necessary dependencies for your platform. For detailed instructions, refer to the Raylib documentation.

2. **Update System Environment Variables**:

   Add the following path to your system environment variables:
   ```bash
   C:\raylib\w64devkit\bin
   ```

3. **Navigate to Source Directory**:

   Open a terminal and navigate to the following path:
   ```bash
   C:\raylib\raylib\src
   ```

4. **Compile Raylib**:

   In the terminal, run the following command:
   ```bash
   mingw32-make PLATFORM=PLATFORM_DESKTOP
   ```

5. **Locate Compiled Library**:

   After the command executes successfully, a new file named ```libraylib.a``` will be created.

6. **Replace Existing Library**:

   Copy the newly created libraylib.a file and replace the existing ```libraylib.a``` file in the lib folder within your project directory.

7. **Create Makefile**:
   ```bash
   **List of source files**
   SOURCES = ./src/fivevar.cpp ./src/fourvar.cpp ./src/grid.cpp ./src/kmapsolver.cpp ./src/main.cpp ./src/threevar.cpp ./src/twovar.cpp ./src/http_request.cpp

   # List of object files (replace .cpp with .o)
   OBJECTS = $(SOURCES:.cpp=.o)

   # Include directory for your headers
   INCLUDE_DIRS_PROJECT = include/
   INCLUDE_DIRS_CURL = C:/curl/include

   # Library directories for linking
   LIB_DIRS_PROJECT = lib/
   LIB_DIRS_CURL = C:/curl/lib

   # Compiler and linker flags
   CXXFLAGS = -g -O1 -Wall -Wno-missing-braces -I $(INCLUDE_DIRS_CURL) -I $(INCLUDE_DIRS_PROJECT)
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
   ```


8. **Run the Program**:

   To compile and run the program, execute the following command in the terminal:
   ```bash
   make
   ```
## Usage
Click on the cells in the K-Map Grid to flip between 0 and 1. After configuring your K-Map, click the "Calculate" button to compute the minterms. The "Visualize" option allows you to see the K-Map Expression using logic gates.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the [MIT License](LICENSE).
