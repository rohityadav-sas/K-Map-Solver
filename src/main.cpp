#include <raylib.h>
#include "grid.h"
#include "gridSub.h"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    const int screenWidth = 600;
    const int screenHeight = 600;
    twoVar grid;

    InitWindow(screenWidth, screenHeight, "K-Map Solver");

    SetTargetFPS(10);
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(darkGreen);
            grid.Draw();
            grid.listenClick();
            grid.calculateButton();
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
}