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
    Rectangle Reset;
    Rectangle Result;
    Color CalculateColor, CalculateColorHover, ResetColor, ResetColorHover;
    Color cellSelected = {212, 180, 125, 255};
    std::string result;
    Font Bodyfont;
    std::vector<int> minterms;

public:
    Grid();
    void Initialize();
    void listenClick();
    void printResult(int ox, int oy, int rw, int rectWidth, int rectHeight, Font Bodyfont);
    void listenHover();
    void calculateButton(Font Bodyfont);
    void visualizeButton(Font Bodyfont);
    void resultButton(Font Bodyfont);
    std::string solveKMap(int numberOfVariables, int numberOfMinterms, std::vector<int> minterms);
    int calculateNumberOfVariables(int rows, int cols);
    std::vector<int> returnMinterms();
    bool resultCalculated = false;
    void visualizeKmap();
    void SimulateLoading(float duration);
};