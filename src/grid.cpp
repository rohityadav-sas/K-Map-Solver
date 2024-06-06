#include "grid.h"
#include <raylib.h>
#include <cstring>
#include <iostream>
#include <algorithm>

// Font font = GetFontDefault();

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
        int col = (mousePos.x - offsetX) / cellSize;
        int row = (mousePos.y - offsetY) / cellSize;
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            grid[row][col] = 1 - grid[row][col];
        }
        else if (mousePos.x >= offsetX + (gridWidth - 200) / 2 && mousePos.x <= offsetX + (gridWidth - 200) / 2 + 200 && mousePos.y >= offsetY + (gridHeight - 50) + gridHeight - 30 && mousePos.y <= offsetY + (gridHeight - 50) + gridHeight - 30 + 50)
        {
            minterms = returnMinterms();
            for (int item : minterms)
            {
                std::cout << item << ",";
            }
            std::cout << std::endl;
        }
    }
}

// void Grid::calculateButton()
// {
//     DrawRectangleRounded(Rectangle{static_cast<float>(offsetX + (gridWidth - 200) / 2), static_cast<float>(offsetY + (gridHeight - 50) + gridHeight - 30), 200, 50}, 0.1, 0, LIGHTGRAY);
//     int textWIDTH = MeasureText("Calculate", 25);
//     DrawTextEx(font, "Calculate", Vector2{static_cast<float>(offsetX + (gridWidth - 200) / 2 + (200 - textWIDTH) / 2) - 5, static_cast<float>(offsetY + (gridHeight - 50) + gridHeight - 30 + (50 - 25) / 2)}, 25, 4, BLACK);
// }

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
                    minterms.push_back(4);
                }
                if (i == 1 && j == 1)
                {
                    minterms.push_back(5);
                }
                if (i == 1 && j == 3)
                {
                    minterms.push_back(6);
                }
                if (i == 1 && j == 2)
                {
                    minterms.push_back(7);
                }
            }
        }
    }
    std::sort(minterms.begin(), minterms.end());
    return minterms;
}
