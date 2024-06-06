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
    Rectangle Cell;
    Rectangle Calculate;
    Color CalculateColor, CalculateColorHover;
    Font font;
    std::vector<int> minterms;

public:
    Grid();
    void Initialize();
    void listenClick();
    void listenHover();
    void calculateButton();
    std::vector<int> returnMinterms();
};