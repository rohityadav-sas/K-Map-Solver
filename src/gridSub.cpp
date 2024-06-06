#include "gridSub.h"
// #include "utils.h"
#include <cstring>

twoVar::twoVar()
{
    rows = 2;
    cols = 2;
    cellSize = 60;
    gridWidth = cols * cellSize;
    gridHeight = rows * cellSize;
    Initialize();
    strcpy(variables[0], "A");
    strcpy(variables[1], "B");
}

threeVar::threeVar()
{
    rows = 2;
    cols = 4;
    cellSize = 60;
    gridWidth = cols * cellSize;
    gridHeight = rows * cellSize;
    Initialize();
    strcpy(variables[0], "A");
    strcpy(variables[1], "BC");
}

fourVar::fourVar()
{
    rows = 4;
    cols = 4;
    cellSize = 60;
    gridWidth = cols * cellSize;
    gridHeight = rows * cellSize;
    Initialize();
    strcpy(variables[0], "AB");
    strcpy(variables[1], "CD");
}