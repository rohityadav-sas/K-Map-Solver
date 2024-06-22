#include <raylib.h> //including the library for GUI
#include "grid.h"
#include "gridSub.h"

int main()
{
    const int screenWidth = 1216;
    const int screenHeight = 809;
    twoVar grid2;
    threeVar grid3;
    fourVar grid4;
    int currentGrid = 0;
    Image icon = LoadImage("./assets/kmap.png");
    InitWindow(screenWidth, screenHeight, "K-Map Solver");
    Texture2D texture = LoadTexture("./assets/bgimg3.png");
    Font Titlefont = LoadFont("./fonts/batman.ttf");
    Font Bodyfont = LoadFont("./fonts/unispace.otf");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(60);
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
            int textWIDTH_title= MeasureText("KMAP SOLVER", 55);
            int textWIDTH2 = MeasureText("Press 2 for 2-variable K-Map", 30);
            int textWIDTH3 = MeasureText("Press 3 for 3-variable K-Map", 30);
            int textWIDTH4 = MeasureText("Press 4 for 4-variable K-Map", 30);
            DrawTextEx(Titlefont, "KMAP SOLVER", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH_title) / 2 - 10, 10}, 55, 4, WHITE);
            DrawTextEx(Bodyfont, "Press 2 for 2-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH2) / 2 - 10, 115}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Press 3 for 3-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH3) / 2 - 10, 145}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Press 4 for 4-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH4) / 2 - 10, 175}, 30, 4, WHITE);

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

            if (currentGrid == 2)
            {
                grid2.Draw();
                grid2.listenClick();
                grid2.listenHover();
                grid2.calculateButton();
                if (grid2.resultCalculated)
                {
                    grid2.resultButton();
                }
                // grid2.resultButton();
                // grid2.printResult();
            }
            if (currentGrid == 3)
            {
                grid3.Draw();
                grid3.listenClick();
                grid3.listenHover();
                grid3.calculateButton();
                if (grid3.resultCalculated)
                {
                    grid3.resultButton();
                }
                // 
                // grid3.resultButton();
                // grid3.printResult();
            }
            if (currentGrid == 4)
            {
                grid4.Draw();
                grid4.listenClick();
                grid4.listenHover();
                grid4.calculateButton();
                if (grid4.resultCalculated)
                {
                    grid4.resultButton();
                }
                // 
                // grid4.resultButton();
                // grid4.printResult();
            }

            EndDrawing();
        }
        UnloadTexture(texture);
        UnloadFont(Titlefont);
        UnloadFont(Bodyfont);
        CloseWindow();
        return 0;
    }
}