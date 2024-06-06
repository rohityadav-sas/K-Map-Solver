#include "grid.h"
#include <raylib.h>
#include <cstring>
#include <iostream>
#include <algorithm>

Grid::Grid()
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

Font font = GetFontDefault();

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

void Grid::Draw()
{

    offsetX = (GetScreenWidth() - gridWidth) / 2;
    offsetY = (GetScreenHeight() - gridHeight) / 2;
    DrawTextEx(font, variables[0], Vector2{static_cast<float>(offsetX - cellSize), static_cast<float>(offsetY - cellSize / 2)}, 30, 0, BLACK);
    DrawTextEx(font, variables[1], Vector2{static_cast<float>(offsetX - 25 - 5), static_cast<float>(offsetY - cellSize - 10)}, 30, 4, BLACK);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            DrawRectangle(j * cellSize + offsetX + 1, i * cellSize + offsetY + 1, cellSize - 1, cellSize - 1, WHITE);
            if (i == 0 && j == 0)
            {
                DrawLineEx(Vector2{static_cast<float>(j * cellSize + offsetX + 1), static_cast<float>(i * cellSize + offsetY + 1)}, Vector2{static_cast<float>(j * cellSize + offsetX + 1 - cellSize), static_cast<float>(i * cellSize + offsetY + 1 - cellSize)}, 3.0f, BLACK);
            }
            sprintf(cellValue, "%d", grid[i][j]);
            int textWidth = MeasureText(cellValue, 35);
            DrawTextEx(font, cellValue,
                       Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWidth) / 2),
                               static_cast<float>(i * cellSize + offsetY + (cellSize - 35) / 2)},
                       35, 0, BLACK);
            if (j == 0 && i == 0)
            {
                int textWIDTH = MeasureText("00", 25);
                DrawTextEx(font, "0", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 4, BLACK);
                DrawTextEx(font, "00", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 4, BLACK);
            }
            if (i == 1 && j == 0)
            {
                int textWIDTH = MeasureText("01", 25);
                DrawTextEx(font, "1", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 8, BLACK);
            }
            if (i == 0 && j == 1)
            {
                int textWIDTH = MeasureText("01", 25);
                DrawTextEx(font, "01", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 8, BLACK);
            }
            if (i == 0 && j == 2)
            {
                int textWIDTH = MeasureText("11", 25);
                DrawTextEx(font, "11", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 8, BLACK);
            }
            if (i == 0 && j == 3)
            {
                int textWIDTH = MeasureText("10", 25);
                DrawTextEx(font, "10", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 8, BLACK);
            }
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

void Grid::calculateButton()
{
    DrawRectangleRounded(Rectangle{static_cast<float>(offsetX + (gridWidth - 200) / 2), static_cast<float>(offsetY + (gridHeight - 50) + gridHeight - 30), 200, 50}, 0.1, 0, LIGHTGRAY);
    int textWIDTH = MeasureText("Calculate", 25);
    DrawTextEx(font, "Calculate", Vector2{static_cast<float>(offsetX + (gridWidth - 200) / 2 + (200 - textWIDTH) / 2) - 5, static_cast<float>(offsetY + (gridHeight - 50) + gridHeight - 30 + (50 - 25) / 2)}, 25, 4, BLACK);
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
