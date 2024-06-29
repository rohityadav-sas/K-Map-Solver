#include <raylib.h>
#include "grid.h"
#include "gridSub.h"

enum Screen
{
    HOME = 0,
    TWOVAR,
    THREEVAR,
    FOURVAR,
    FIVEVAR
};

const int screenWidth = 1216;
const int screenHeight = 1000;
const char *buttonTexts[4] = {"2", "3", "4", "5"};
Color buttonColors[4] = {WHITE, WHITE, WHITE, WHITE};
Rectangle buttons[4] = {
    {screenWidth / 5 - 25, 225, 50, 50},
    {(2 * screenWidth) / 5 - 25, 225, 50, 50},
    {(3 * screenWidth) / 5 - 25, 225, 50, 50},
    {(4 * screenWidth) / 5 - 25, 225, 50, 50}};
void DrawButtons(int);
void listenHover();

int main()
{
    twoVar grid2;
    threeVar grid3;
    fourVar grid4;
    fiveVar grid5;
    int currentGrid = 0;
    Image icon = LoadImage("./assets/kmap.png");
    InitWindow(screenWidth, screenHeight, "K-Map Solver");
    Screen currentScreen = HOME;
    Texture2D texture = LoadTexture("./assets/bgimg3.png");
    Font Titlefont = LoadFont("./fonts/batman.ttf");
    Font Bodyfont = LoadFont("./fonts/unispace.ttf");
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
            DrawTextEx(Titlefont, "KMAP SOLVER", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH_title) / 2 - 25, 10}, 55, 4, WHITE);
            Vector2 mousePoint = GetMousePosition();

            int textWIDTH2 = MeasureText("Click '2' for 2-variable K-Map", 30);
            int textWIDTH3 = MeasureText("Click '3' for 3-variable K-Map", 30);
            int textWIDTH4 = MeasureText("Click '4' for 4-variable K-Map", 30);
            int textWIDTH5 = MeasureText("Click '5' for 5-variable K-Map", 30);
            DrawTextEx(Bodyfont, "Click '2' for 2-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH2) / 2 - 10, 75}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Click '3' for 3-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH3) / 2 - 10, 105}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Click '4' for 4-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH4) / 2 - 10, 135}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "Click '5' for 5-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH5) / 2 - 10, 165}, 30, 4, WHITE);
            for (int i = 0; i < 4; i++)
            {
                DrawRectangleRec(buttons[i], buttonColors[i]);
                DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
            }

            if (currentScreen == HOME)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = GREEN;
                        buttonColors[0] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[0] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[0] = WHITE;
                        currentScreen = FIVEVAR;
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
                        buttonColors[1] = GREEN;
                        buttonColors[0] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[0] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[0] = WHITE;
                        currentScreen = FIVEVAR;
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
                        buttonColors[0] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[0] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[0] = WHITE;
                        currentScreen = FIVEVAR;
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
                        buttonColors[0] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = GREEN;
                        buttonColors[0] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[0] = WHITE;
                        currentScreen = FIVEVAR;
                    }
                }
            }
            else if (currentScreen == FIVEVAR)
            {
                currentGrid = 5;
                DrawButtons(5);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = GREEN;
                        buttonColors[0] = WHITE;
                        buttonColors[2] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = GREEN;
                        buttonColors[1] = WHITE;
                        buttonColors[0] = WHITE;
                        buttonColors[3] = WHITE;
                        currentScreen = FOURVAR;
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
                    grid2.resultButton(Bodyfont);
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
                    grid3.resultButton(Bodyfont);
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
                    grid4.resultButton(Bodyfont);
                }
            }
            if (currentGrid == 5)
            {
                grid5.Draw();
                grid5.listenClick();
                grid5.listenHover();
                grid5.calculateButton();
                if (grid5.resultCalculated)
                {
                    grid5.resultButton(Bodyfont);
                }
            }
            listenHover();

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
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
    else if (currentGrid == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
    else if (currentGrid == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
    else if (currentGrid == 5)
    {
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(buttons[i], buttonColors[i]);
            DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2, buttons[i].y + (50 - 20) / 2, 20, BLACK);
        }
    }
}

void listenHover()
{
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, buttons[0]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[0].r == WHITE.r && buttonColors[0].g == WHITE.g && buttonColors[0].b == WHITE.b && buttonColors[0].a == WHITE.a)
        {
            buttonColors[0] = GRAY;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[1].r == WHITE.r && buttonColors[1].g == WHITE.g && buttonColors[1].b == WHITE.b && buttonColors[1].a == WHITE.a)
        {
            buttonColors[1] = GRAY;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[2].r == WHITE.r && buttonColors[2].g == WHITE.g && buttonColors[2].b == WHITE.b && buttonColors[2].a == WHITE.a)
        {
            buttonColors[2] = GRAY;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[3].r == WHITE.r && buttonColors[3].g == WHITE.g && buttonColors[3].b == WHITE.b && buttonColors[3].a == WHITE.a)
        {
            buttonColors[3] = GRAY;
        }
    }
    else
    {
        std::cout << "else case entered" << std::endl;
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        if (buttonColors[0].r == GRAY.r && buttonColors[0].g == GRAY.g && buttonColors[0].b == GRAY.b && buttonColors[0].a == GRAY.a)
        {
            buttonColors[0] = WHITE;
        }
        if (buttonColors[1].r == GRAY.r && buttonColors[1].g == GRAY.g && buttonColors[1].b == GRAY.b && buttonColors[1].a == GRAY.a)
        {
            buttonColors[1] = WHITE;
        }
        if (buttonColors[2].r == GRAY.r && buttonColors[2].g == GRAY.g && buttonColors[2].b == GRAY.b && buttonColors[2].a == GRAY.a)
        {
            buttonColors[2] = WHITE;
        }
        if (buttonColors[3].r == GRAY.r && buttonColors[3].g == GRAY.g && buttonColors[3].b == GRAY.b && buttonColors[3].a == GRAY.a)
        {
            buttonColors[3] = WHITE;
        }
    }
}