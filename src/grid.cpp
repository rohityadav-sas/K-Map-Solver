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
    CalculateColor = {255, 248, 219, 255};
    CalculateColorHover = {223, 224, 223, 255};
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
            for (const auto &minterm : minterms)
            {
                std::cout << minterm << " ";
            }
            std::cout << std::endl;
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
        CalculateColor = {255, 248, 219, 255};
    }
}

void Grid::calculateButton(Font Bodyfont)
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
    int twoVar[2][2] = {
        {0, 1},
        {2, 3}};
    int threeVar[2][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6}};
    int fourVar[4][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6},
        {12, 13, 15, 14},
        {8, 9, 11, 10}};
    int fiveVar[4][8] = {
        {0, 1, 3, 2, 6, 7, 5, 4},
        {8, 9, 11, 10, 14, 15, 13, 12},
        {24, 25, 27, 26, 30, 31, 29, 28},
        {16, 17, 19, 18, 22, 23, 21, 20}};

    std::vector<int> minterms;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (grid[row][col] == 1)
            {
                if (rows == 2 && cols == 2)
                {
                    minterms.push_back(twoVar[row][col]);
                }
                else if (rows == 2 && cols == 4)
                {
                    minterms.push_back(threeVar[row][col]);
                }
                else if (rows == 4 && cols == 4)
                {
                    minterms.push_back(fourVar[row][col]);
                }
                else if (rows == 4 && cols == 8)
                {
                    minterms.push_back(fiveVar[row][col]);
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
    else if (minimizedExpression == "A XOR B XOR C XOR D XOR E")
    {
        minimizedExpression = "A XOR B XOR C XOR D XOR E";
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