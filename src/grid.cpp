#include "kmapsolver.h"
#include "grid.h"
#include <raylib.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

Grid::Grid()
{
    CalculateColor = LIGHTGRAY;
    CalculateColorHover = {170, 170, 170, 255};
}

void Grid::Initialize()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::listenClick()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x;
        int y = mousePos.y;
        int col = (x - offsetX) / cellSize;
        int row = (y - offsetY) / cellSize;
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            grid[row][col] = 1 - grid[row][col];
        }
        else if (CheckCollisionPointRec(mousePos, Calculate))
        {
            minterms = returnMinterms();
            int numberOfVariables = calculateNumberOfVariables(rows, cols);
            int numberOfMinterms = minterms.size();
            result = Grid::solveKMap(numberOfVariables, numberOfMinterms, minterms);
        }
    }
}

void Grid::printResult()
{
    const char *resultCStr = result.c_str();
    DrawTextEx(font, resultCStr, Vector2{static_cast<float>(offsetX + 20), static_cast<float>(offsetY + gridHeight + 20 + 50 + 20 + (50 - 22) / 2)}, 22, 4, BLACK);
}

void Grid::listenHover()
{
    Vector2 mousePos = GetMousePosition();
    int x = mousePos.x;
    int y = mousePos.y;
    int col = (x - offsetX) / cellSize;
    int row = (y - offsetY) / cellSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else if (CheckCollisionPointRec(mousePos, Calculate))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        CalculateColor = CalculateColorHover;
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        CalculateColor = LIGHTGRAY;
    }
}

void Grid::calculateButton()
{
    Calculate = {static_cast<float>(offsetX),
                 static_cast<float>(offsetY + gridHeight + 20),
                 static_cast<float>(gridWidth),
                 50};
    DrawRectangleRounded(Calculate, 0.1, 0, CalculateColor);
    int textWIDTH = MeasureText("Calculate", 15);
    DrawTextEx(font, "Calculate", Vector2{static_cast<float>(offsetX + (gridWidth - textWIDTH) / 2 - 10), static_cast<float>(offsetY + gridHeight + 20 + (50 - 15) / 2)}, 15, 4, BLACK);
}

void Grid::resultButton()
{
    Result = {static_cast<float>(offsetX),
              static_cast<float>(offsetY + gridHeight + 20 + 50 + 20),
              static_cast<float>(gridWidth),
              50};
    DrawRectangleRounded(Result, 0.1, 0, WHITE);
    int textWIDTH = MeasureText("Result:", 22);
    DrawTextEx(font, "Result:", Vector2{static_cast<float>(offsetX - (gridWidth - textWIDTH) / 2 - 80), static_cast<float>(offsetY + gridHeight + 20 + 50 + 20 + (50 - 22) / 2)}, 22, 4, BLACK);
}

std::vector<int> Grid::returnMinterms()
{
    std::vector<int> minterms;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
            {
                if (i == 0 && j == 0)
                {
                    minterms.push_back(0);
                }
                if (i == 0 && j == 1)
                {
                    minterms.push_back(1);
                }
                if (i == 0 && j == 3)
                {
                    minterms.push_back(2);
                }
                if (i == 0 && j == 2)
                {
                    minterms.push_back(3);
                }
                if (i == 1 && j == 0)
                {
                    if (cols == 2)
                    {
                        minterms.push_back(2);
                    }
                    else
                    {
                        minterms.push_back(4);
                    }
                }
                if (i == 1 && j == 1)
                {
                    if (cols == 2)
                    {
                        minterms.push_back(3);
                    }
                    else
                    {
                        minterms.push_back(5);
                    }
                }
                if (i == 1 && j == 3)
                {
                    minterms.push_back(6);
                }
                if (i == 1 && j == 2)
                {
                    minterms.push_back(7);
                }
                if (i == 3 && j == 0)
                {
                    minterms.push_back(8);
                }
                if (i == 3 && j == 1)
                {
                    minterms.push_back(9);
                }
                if (i == 3 && j == 3)
                {
                    minterms.push_back(10);
                }
                if (i == 3 && j == 2)
                {
                    minterms.push_back(11);
                }
                if (i == 2 && j == 0)
                {
                    minterms.push_back(12);
                }
                if (i == 2 && j == 1)
                {
                    minterms.push_back(13);
                }
                if (i == 2 && j == 3)
                {
                    minterms.push_back(14);
                }
                if (i == 2 && j == 2)
                {
                    minterms.push_back(15);
                }
            }
        }
    }
    std::sort(minterms.begin(), minterms.end());
    return minterms;
}

int Grid::calculateNumberOfVariables(int rows, int cols)
{
    int noOfCells = rows * cols;
    return log2(noOfCells);
}

std::string Grid::solveKMap(int numberOfVariables, int numberOfMinterms, std::vector<int> minterms)
{
    std::vector<std::string> primeImplicants = minimizeKMap(numberOfVariables, minterms);

    std::cout << "The minimized logic expression is: ";
    std::string minimizedExpression;
    for (size_t i = 0; i < primeImplicants.size(); ++i)
    {
        minimizedExpression += formatImplicant(primeImplicants[i], numberOfVariables);
        if (i < primeImplicants.size() - 1)
        {
            minimizedExpression += " + ";
        }
    }
    if (minimizedExpression.empty())
    {
        minimizedExpression = "1";
    }
    return minimizedExpression;
}