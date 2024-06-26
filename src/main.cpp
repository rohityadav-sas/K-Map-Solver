#include <raylib.h>
#include "grid.h"
#include "gridSub.h"

enum Screen
{
    HOME = 0,
    TWOVAR,
    THREEVAR,
    FOURVAR
};

const int screenWidth = 1216;
const int screenHeight = 809;
const char *buttonTexts[3] = {"2", "3", "4"};
Color buttonColors[3] = {WHITE, WHITE, WHITE};
Rectangle buttons[3] = {
    {screenWidth / 4 - 25, 185, 50, 50},
    {(2 * screenWidth) / 4 - 25, 185, 50, 50},
    {(3 * screenWidth) / 4 - 25, 185, 50, 50}};
void DrawButtons(int);

int main()
{
    twoVar grid2;
    threeVar grid3;
    fourVar grid4;
    int currentGrid = 0;
    Image icon = LoadImage("./assets/kmap.png");
    InitWindow(screenWidth, screenHeight, "K-Map Solver");
    Screen currentScreen = HOME;
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
            DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
            int textWIDTH_title = MeasureText("KMAP SOLVER", 55);
            DrawTextEx(Titlefont, "KMAP SOLVER", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH_title) / 2 - 10, 10}, 55, 4, WHITE);
            Vector2 mousePoint = GetMousePosition();

            int textWIDTH2 = MeasureText("Click '2' for 2-variable K-Map", 30);
            int textWIDTH3 = MeasureText("Click '3' for 3-variable K-Map", 30);
            int textWIDTH4 = MeasureText("Click '4' for 4-variable K-Map", 30);
            DrawTextEx(Bodyfont, "Click '2' for 2-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH2) / 2 - 10, 75}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Click '3' for 3-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH3) / 2 - 10, 105}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Click '4' for 4-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH4) / 2 - 10, 135}, 30, 4, WHITE);
            for (int i = 0; i < 3; i++)
            {
                buttonColors[i] = WHITE;
                DrawRectangleRec(buttons[i], buttonColors[i]);
                DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
            }

            if (currentScreen == HOME)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        currentScreen = FOURVAR;
                    }
                }
            }
            else if (currentScreen == TWOVAR)
            {
                currentGrid = 2;
                DrawButtons(2);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        currentScreen = FOURVAR;
                    }
                }
            }
            else if (currentScreen == THREEVAR)
            {
                currentGrid = 3;
                DrawButtons(3);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        currentScreen = FOURVAR;
                    }
                }
            }
            else if (currentScreen == FOURVAR)
            {
                currentGrid = 4;
                DrawButtons(4);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        currentScreen = THREEVAR;
                    }
                }
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
void DrawButtons(int currentGrid)
{
    if (currentGrid == 2)
    {
        buttonColors[0] = GREEN;
        buttonColors[1] = WHITE;
        buttonColors[2] = WHITE;
        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
    else if (currentGrid == 3)
    {
        buttonColors[0] = WHITE;
        buttonColors[1] = GREEN;
        buttonColors[2] = WHITE;
        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
    else if (currentGrid == 4)
    {
        buttonColors[0] = WHITE;
        buttonColors[1] = WHITE;
        buttonColors[2] = GREEN;
        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
}
