#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>

class Grid
{
protected:
    int rows;
    int cols;
    int cellSize;
    int offsetX;
    int offsetY;
    int gridWidth;
    int gridHeight;
    int grid[20][30];
    char cellValue[2];
    Font font;
    std::vector<int> minterms;

public:
    void Initialize();
    void listenClick();
    void calculateButton();
    std::vector<int> returnMinterms();
};