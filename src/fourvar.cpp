#include "gridSub.h"
#include <cstring>

fourVar::fourVar()
{
    font = GetFontDefault();
    rows = 4;
    cols = 4;
    cellSize = 60;
    gridWidth = cols * cellSize;
    gridHeight = rows * cellSize;
    Initialize();
}

void fourVar::Draw()
{

    offsetX = (GetScreenWidth() - gridWidth) / 2;
    offsetY = (GetScreenHeight() - gridHeight) / 2;
    DrawTextEx(font, "AB", Vector2{static_cast<float>(offsetX - cellSize - 15), static_cast<float>(offsetY - cellSize / 2)}, 30, 4, BLACK);
    DrawTextEx(font, "CD", Vector2{static_cast<float>(offsetX - 25 - 5), static_cast<float>(offsetY - cellSize - 5)}, 30, 4, BLACK);

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
            if (i == 0 && j == 0)
            {
                int textWIDTH = MeasureText("00", 25);
                DrawTextEx(font, "00", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 4, BLACK);
                DrawTextEx(font, "00", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 4, BLACK);
            }
            if (i == 1 && j == 0)
            {
                int textWIDTH = MeasureText("01", 25);
                DrawTextEx(font, "01", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 8, BLACK);
            }
            if (i == 2 && j == 0)
            {
                int textWIDTH = MeasureText("11", 25);
                DrawTextEx(font, "11", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 8, BLACK);
            }
            if (i == 3 && j == 0)
            {
                int textWIDTH = MeasureText("10", 25);
                DrawTextEx(font, "10", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 8, BLACK);
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