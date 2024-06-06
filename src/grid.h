#pragma once
#include <iostream>
#include <vector>

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
    char variables[2][2];
    std::vector<int> minterms;

public:
    Grid();
    void Initialize();
    void Draw();
    void listenClick();
    void calculateButton();
    std::vector<int> returnMinterms();
};