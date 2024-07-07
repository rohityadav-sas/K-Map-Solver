# Karnaugh Map (K-Map) Solver in C++
This project is a Karnaugh Map (KMap) Solver written in C++. It's currently under development and uses the Raylib library for the graphical user interface.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features
- [x] Interactive K-Map Grid
- [x] Calculation of MinTerms
- [x] Supported upto 5 variables
- [x] Simplification of Boolean expressions

## Installation

1. **Install Dependencies**:

   Ensure you have installed all necessary dependencies for your platform. For detailed instructions, refer to the Raylib documentation.

2. **Update System Environment Variables**:

   Add the following path to your system environment variables:
   ```bash
   C:\raylib\w64devkit\bin

3. **Navigate to Source Directory**:

   Open a terminal and navigate to the following path:
   ```bash
   C:\raylib\raylib\src

4. **Compile Raylib**:

   In the terminal, run the following command:
   ```bash
   mingw32-make PLATFORM=PLATFORM_DESKTOP

5. **Locate Compiled Library**:

   After the command executes successfully, a new file named ```libraylib.a``` will be created.

6. **Replace Existing Library**:

   Copy the newly created libraylib.a file and replace the existing ```libraylib.a``` file in the lib folder within your project directory.

7. **Create Makefile**:

   Create a Makefile in your project directory and add the following content:
   ```bash
   # Define the source files for the project
   SOURCES = ./src/fourvar.cpp ./src/grid.cpp ./src/kmapsolver.cpp ./src/main.cpp ./src/threevar.cpp ./src/twovar.cpp

   # Default target to compile the project
   default:
    # Compile the source files into an executable named game.exe
    g++ $(SOURCES) -o ./build/game.exe -g -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
    
    # Run the compiled executable
    ./build/game.exe


8. **Run the Program**:

   To compile and run the program, execute the following command in the terminal:
   ```bash
   make
   
## Usage
Click on the cells in the KMap grid to toggle between 0 and 1. After setting up your KMap, click on the "Calculate" button to calculate the minterms.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the [MIT License](LICENSE).