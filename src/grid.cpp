#include "kmapsolver.h"
#include "grid.h"
#include <raylib.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

bool checkForXOR(std::string &minimizedExpression);
void checkForXOR2(std::string &minimizedExpression);

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
            resultCalculated = true;
        }
    }
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
    DrawTextEx(Bodyfont, "Calculate", Vector2{static_cast<float>(offsetX + (gridWidth - textWIDTH) / 2 - 10), static_cast<float>(offsetY + gridHeight + 20 + (50 - 15) / 2)}, 15, 4, BLACK);
}

void Grid::resultButton(Font Bodyfont)
{
    Vector2 resultWidth1 = MeasureTextEx(Bodyfont, result.c_str(), 22, 2);
    int resultWidth = resultWidth1.x;
    int rectWidth = resultWidth + 30;
    int offSetX = (GetScreenWidth() - rectWidth) / 2;
    int offSetY = (GetScreenHeight() - gridHeight) / 2 + gridHeight + 100;

    DrawRectangleRounded({static_cast<float>(offSetX), static_cast<float>(offSetY), static_cast<float>(rectWidth), 50}, 0.1, 0, WHITE);
    DrawTextEx(Bodyfont, "Result: ", Vector2{static_cast<float>(offSetX - 100), static_cast<float>(offSetY + (50 - 22) / 2)}, 22, 4, WHITE);
    printResult(offSetX, offSetY, resultWidth, resultWidth + 50, 50, Bodyfont);
}

void Grid::printResult(int ox, int oy, int rw, int rectWidth, int rectHeight, Font Bodyfont)
{
    DrawTextEx(Bodyfont, result.c_str(), Vector2{static_cast<float>(ox + 15), static_cast<float>(oy + (50 - 22) / 2)}, 22, 2, BLACK);
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

    std::string minimizedExpression;
    for (size_t i = 0; i < primeImplicants.size(); ++i)
    {
        minimizedExpression += formatImplicant(primeImplicants[i], numberOfVariables);
        if (checkForXOR(minimizedExpression))
        {
            return minimizedExpression;
        }
        if (i < primeImplicants.size() - 1)
        {
            minimizedExpression += " + ";
        }
    }
    if (minimizedExpression.empty())
    {
        minimizedExpression = "1";
    }
    checkForXOR2(minimizedExpression);
    return minimizedExpression;
}

bool checkForXOR(std::string &minimizedExpression)
{
    if (minimizedExpression == "A XOR B")
    {
        minimizedExpression = "A XOR B";
        return true;
    }
    else if (minimizedExpression == "A XOR B XOR C")
    {
        minimizedExpression = "A XOR B XOR C";
        return true;
    }
    else if (minimizedExpression == "A XOR B XOR C XOR D")
    {
        minimizedExpression = "A XOR B XOR C XOR D";
        return true;
    }
    return false;
}

void checkForXOR2(std::string &minimizedExpression)
{
    if (minimizedExpression == "A'B + AB'")
    {
        minimizedExpression = "A XOR B";
    }
    else if (minimizedExpression == "AC' + AC'")
    {
        minimizedExpression = "A XOR C";
    }
    else if (minimizedExpression == "A'D + AD'")
    {
        minimizedExpression = "A XOR D";
    }
    else if (minimizedExpression == "B'C + BC'")
    {
        minimizedExpression = "B XOR C";
    }
    else if (minimizedExpression == "B'D + BD'")
    {
        minimizedExpression = "B XOR D";
    }
    else if (minimizedExpression == "C'D + CD'")
    {
        minimizedExpression = "C XOR D";
    }
}