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
Color buttonColor = {252, 250, 237, 255};
Color buttonColor_onHover = {235, 229, 212, 255};
Color buttonColor_onClick = {255, 226, 172, 255};
Color buttonColors[4] = {buttonColor, buttonColor, buttonColor, buttonColor};
Rectangle buttons[4] = {
    {screenWidth / 5 - 25, 225, 70, 50},
    {(2 * screenWidth) / 5 - 25, 225, 70, 50},
    {(3 * screenWidth) / 5 - 25, 225, 70, 50},
    {(4 * screenWidth) / 5 - 25, 225, 70, 50}};
void listenHover(); // changes color and mouse pointer when hovered over variable buttons

int main()
{
    // Objects for drawing each variable grids
    twoVar grid2;
    threeVar grid3;
    fourVar grid4;
    fiveVar grid5;
    int currentGrid = 0; // So that no grid is drawin when window loads
    Image icon = LoadImage("./assets/icon.png");
    InitWindow(screenWidth, screenHeight, "K-Map Solver"); // initializes the window
    Screen currentScreen = HOME;                           // sets the loaded window to HOME screen
    Texture2D texture = LoadTexture("./assets/bgimg3.png");
    Font Titlefont = LoadFont("./fonts/batman.ttf");
    Font Bodyfont = LoadFont("./fonts/unispace.ttf");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(60); // Window FPS
    {
        while (!WindowShouldClose()) // Run the code until you close the window
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
            int textWIDTH_title = MeasureText("KMAP SOLVER", 55);
            DrawTextEx(Titlefont, "KMAP SOLVER", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH_title) / 2 - 25, 10}, 55, 4, {38, 22, 1, 255});
            Vector2 mousePoint = GetMousePosition();

            int textWIDTH2 = MeasureText("      Click '2' for 2-variable K-Map", 30);
            int textWIDTH3 = MeasureText("      Click '3' for 3-variable K-Map", 30);
            int textWIDTH4 = MeasureText("      Click '4' for 4-variable K-Map", 30);
            int textWIDTH5 = MeasureText("      Click '5' for 5-variable K-Map", 30);
            DrawTextEx(Bodyfont, "      Click '2' for 2-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH2) / 2 - 10, 75}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "      Click '3' for 3-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH3) / 2 - 10, 105}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "      Click '4' for 4-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH4) / 2 - 10, 135}, 30, 4, WHITE);
            DrawTextEx(Bodyfont, "      Click '5' for 5-variable K-Map", Vector2{static_cast<float>(GetScreenWidth() - textWIDTH5) / 2 - 10, 165}, 30, 4, WHITE);
            for (int i = 0; i < 4; i++)
            {
                DrawRectangleRounded(buttons[i], 0.2, 0, buttonColors[i]);
                DrawText(buttonTexts[i], buttons[i].x + (50 - MeasureText(buttonTexts[i], 22)) / 2 + 10, buttons[i].y + (50 - 20) / 2, 20, BLACK);
            }
            listenHover(); // checks mouse hover over the variable option's buttons

            if (currentScreen == HOME)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = buttonColor_onClick;
                        buttonColors[0] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[0] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[0] = buttonColor;
                        currentScreen = FIVEVAR;
                    }
                }
            }
            else if (currentScreen == TWOVAR)
            {
                currentGrid = 2;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = buttonColor_onClick;
                        buttonColors[0] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[0] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[0] = buttonColor;
                        currentScreen = FIVEVAR;
                    }
                }
            }
            else if (currentScreen == THREEVAR)
            {
                currentGrid = 3;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[0] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = FOURVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[0] = buttonColor;
                        currentScreen = FIVEVAR;
                    }
                }
            }
            else if (currentScreen == FOURVAR)
            {
                currentGrid = 4;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = buttonColor_onClick;
                        buttonColors[0] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
                    {
                        buttonColors[3] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[0] = buttonColor;
                        currentScreen = FIVEVAR;
                    }
                }
            }
            else if (currentScreen == FIVEVAR)
            {
                currentGrid = 5;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (CheckCollisionPointRec(mousePoint, buttons[0]))
                    {
                        buttonColors[0] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = TWOVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
                    {
                        buttonColors[1] = buttonColor_onClick;
                        buttonColors[0] = buttonColor;
                        buttonColors[2] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = THREEVAR;
                    }
                    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
                    {
                        buttonColors[2] = buttonColor_onClick;
                        buttonColors[1] = buttonColor;
                        buttonColors[0] = buttonColor;
                        buttonColors[3] = buttonColor;
                        currentScreen = FOURVAR;
                    }
                }
            }

            if (currentGrid == 2) // if curentScreen is TWOVAR then currentGrid is 2. So it draws the two variable's grid
            {
                grid2.Draw();                    // draw method draws the grid
                grid2.listenClick();             // Changes 1 to 0 and 0 to 1 when clicked inside the grid cells
                grid2.listenHover();             // changes mouse pointer to pointing hand when hovered over grid area
                grid2.calculateButton(Bodyfont); // Draws the calculate button
                grid2.visualizeButton(Bodyfont); // Draws the visualize button
                if (grid2.resultCalculated)      // Draws 'Result: [Result Expression]' if resultCalulated is True
                {
                    grid2.resultButton(Bodyfont);
                }
            }
            if (currentGrid == 3)
            {
                grid3.Draw();
                grid3.listenClick();
                grid3.listenHover();
                grid3.calculateButton(Bodyfont);
                grid3.visualizeButton(Bodyfont);
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
                grid4.calculateButton(Bodyfont);
                grid4.visualizeButton(Bodyfont);
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
                grid5.calculateButton(Bodyfont);
                grid5.visualizeButton(Bodyfont);
                if (grid5.resultCalculated)
                {
                    grid5.resultButton(Bodyfont);
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
void listenHover()
{
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, buttons[0]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[0].r == buttonColor.r && buttonColors[0].g == buttonColor.g && buttonColors[0].b == buttonColor.b && buttonColors[0].a == buttonColor.a)
        {
            buttonColors[0] = buttonColor_onHover;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[1]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[1].r == buttonColor.r && buttonColors[1].g == buttonColor.g && buttonColors[1].b == buttonColor.b && buttonColors[1].a == buttonColor.a)
        {
            buttonColors[1] = buttonColor_onHover;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[2]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[2].r == buttonColor.r && buttonColors[2].g == buttonColor.g && buttonColors[2].b == buttonColor.b && buttonColors[2].a == buttonColor.a)
        {
            buttonColors[2] = buttonColor_onHover;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, buttons[3]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (buttonColors[3].r == buttonColor.r && buttonColors[3].g == buttonColor.g && buttonColors[3].b == buttonColor.b && buttonColors[3].a == buttonColor.a)
        {
            buttonColors[3] = buttonColor_onHover;
        }
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        if (buttonColors[0].r == buttonColor_onHover.r && buttonColors[0].g == buttonColor_onHover.g && buttonColors[0].b == buttonColor_onHover.b && buttonColors[0].a == buttonColor_onHover.a)
        {
            buttonColors[0] = buttonColor;
        }
        if (buttonColors[1].r == buttonColor_onHover.r && buttonColors[1].g == buttonColor_onHover.g && buttonColors[1].b == buttonColor_onHover.b && buttonColors[1].a == buttonColor_onHover.a)
        {
            buttonColors[1] = buttonColor;
        }
        if (buttonColors[2].r == buttonColor_onHover.r && buttonColors[2].g == buttonColor_onHover.g && buttonColors[2].b == buttonColor_onHover.b && buttonColors[2].a == buttonColor_onHover.a)
        {
            buttonColors[2] = buttonColor;
        }
        if (buttonColors[3].r == buttonColor_onHover.r && buttonColors[3].g == buttonColor_onHover.g && buttonColors[3].b == buttonColor_onHover.b && buttonColors[3].a == buttonColor_onHover.a)
        {
            buttonColors[3] = buttonColor;
        }
    }
}