#include "gridSub.h"
#include <raylib.h>
#include <cstring>

twoVar::twoVar()
{
    Bodyfont = GetFontDefault();
    rows = 2;
    cols = 2;
    cellSize = 60;
    gridWidth = cols * cellSize;
    gridHeight = rows * cellSize;
    Initialize();
}

void twoVar::Draw()
{
    offsetX = (GetScreenWidth() - gridWidth) / 2;
    offsetY = (GetScreenHeight() - gridHeight) / 2;
    DrawTextEx(Bodyfont, "A", Vector2{static_cast<float>(offsetX - cellSize), static_cast<float>(offsetY - cellSize / 2)}, 30, 0, WHITE);
    DrawTextEx(Bodyfont, "B", Vector2{static_cast<float>(offsetX - 25 - 5), static_cast<float>(offsetY - cellSize - 10)}, 30, 4, WHITE);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            DrawRectangle(j * cellSize + offsetX + 1, i * cellSize + offsetY + 1, cellSize - 1, cellSize - 1, grid[i][j] ? YELLOW : WHITE);
            if (i == 0 && j == 0)
            {
                DrawLineEx(Vector2{static_cast<float>(j * cellSize + offsetX + 1), static_cast<float>(i * cellSize + offsetY + 1)}, Vector2{static_cast<float>(j * cellSize + offsetX + 1 - cellSize), static_cast<float>(i * cellSize + offsetY + 1 - cellSize)}, 3.0f, WHITE);
            }
            sprintf(cellValue, "%d", grid[i][j]);
            int textWidth = MeasureText(cellValue, 35);
            DrawTextEx(Bodyfont, cellValue,
                       Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWidth) / 2),
                               static_cast<float>(i * cellSize + offsetY + (cellSize - 35) / 2)},
                       35, 0, BLACK);
            if (j == 0 && i == 0)
            {
                int textWIDTH = MeasureText("0", 25);
                DrawTextEx(Bodyfont, "0", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 4, WHITE);
                DrawTextEx(Bodyfont, "0", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 4, WHITE);
            }
            if (i == 1 && j == 0)
            {
                int textWIDTH = MeasureText("1", 25);
                DrawTextEx(Bodyfont, "1", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2) - cellSize - 10, static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2)}, 25, 8, WHITE);
            }
            if (i == 0 && j == 1)
            {
                int textWIDTH = MeasureText("1", 25);
                DrawTextEx(Bodyfont, "1", Vector2{static_cast<float>(j * cellSize + offsetX + (cellSize - textWIDTH) / 2), static_cast<float>(i * cellSize + offsetY + (cellSize - 25) / 2) - cellSize + 5}, 25, 8, WHITE);
            }
        }
    }
}