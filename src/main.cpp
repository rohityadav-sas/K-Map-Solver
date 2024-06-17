#include <raylib.h>
#include "grid.h"
#include "gridSub.h"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    const int screenWidth = 600;
    const int screenHeight = 600;
    twoVar grid2;
    threeVar grid3;
    fourVar grid4;
    int currentGrid = 2;
    Image icon = LoadImage("favicon/favicon.png");
    InitWindow(screenWidth, screenHeight, "K-Map Solver");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(60);
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(darkGreen);
            int textWIDTH2 = MeasureText("Press 2 for 2-variable K-Map", 20);
            int textWIDTH3 = MeasureText("Press 3 for 3-variable K-Map", 20);
            int textWIDTH4 = MeasureText("Press 4 for 4-variable K-Map", 20);
            DrawTextEx(GetFontDefault(), "Press 2 for 2-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH2) / 2 - 10, 10}, 20, 4, BLACK);
            DrawTextEx(GetFontDefault(), "Press 3 for 3-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH3) / 2 - 10, 40}, 20, 4, BLACK);
            DrawTextEx(GetFontDefault(), "Press 4 for 4-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH4) / 2 - 10, 70}, 20, 4, BLACK);
            if (currentGrid == 2)
            {
                grid2.Draw();
                grid2.listenClick();
                grid2.listenHover();
                grid2.calculateButton();
                grid2.resultButton();
                grid2.printResult();
            }
            if (currentGrid == 3)
            {
                grid3.Draw();
                grid3.listenClick();
                grid3.listenHover();
                grid3.calculateButton();
                grid3.resultButton();
                grid3.printResult();
            }
            if (currentGrid == 4)
            {
                grid4.Draw();
                grid4.listenClick();
                grid4.listenHover();
                grid4.calculateButton();
                grid4.resultButton();
                grid4.printResult();
            }

            if (IsKeyPressed(KEY_TWO))
            {
                currentGrid = 2;
            }
            if (IsKeyPressed(KEY_THREE))
            {
                currentGrid = 3;
            }
            if (IsKeyPressed(KEY_FOUR))
            {
                currentGrid = 4;
            }
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
}