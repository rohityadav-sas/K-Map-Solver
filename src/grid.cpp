#include "kmapsolver.h" // Include the header file for KMapSolver class which likely handles Karnaugh map solving operations
#include "grid.h" // Include the header file for Grid class which likely handles grid-related functionalities
#include <raylib.h> // Include the Raylib library for graphics and game development functions
#include <cstring> // Include the C string library for handling C-style strings and various string manipulation functions
#include <iostream> // Include the input/output stream library for handling standard input and output operations
#include <algorithm> // Include the algorithm library for common algorithms like sorting, searching, etc.
#include <cmath> // Include the math library for mathematical functions and calculations
#include <cstdlib> // Include the standard library for general purpose functions like memory allocation, random number generation, etc.
#include <string> // Include the string library for handling C++ style strings
#include <thread> // Include the thread library for multi-threading functionalities
#include <chrono> // Include the chrono library for time-related functions, such as measuring time intervals
#include <filesystem> // Include the filesystem library for file and directory manipulation
#include <cstdio> // Include the C standard input/output library for C-style input and output functions
#include <future> // Include the future library for asynchronous programming and concurrency
                  // compiler moves on to other lines while compiling  


using namespace std;

namespace fs = std::filesystem;

bool checkForXOR(string &minimizedExpression);

Grid::Grid()
{
    CalculateColor = {255, 248, 219, 255};
    CalculateColorHover = {223, 224, 223, 255};
    ResetColor = {255, 248, 219, 255};
    ResetColorHover = {223, 224, 223, 255};
}

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
        int x = mousePos.x;
        int y = mousePos.y;
        int col = (x - offsetX) / cellSize;
        int row = (y - offsetY) / cellSize;
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            grid[row][col] = 1 - grid[row][col];
        }
        else if (CheckCollisionPointRec(mousePos, Calculate))
        {
            minterms = returnMinterms();
            for (auto i : minterms)
            {
                cout << i << " ";
            }
            cout << endl;
            int numberOfVariables = calculateNumberOfVariables(rows, cols);
            int numberOfMinterms = minterms.size();
            if (minterms.size())
            {
                result = Grid::solveKMap(numberOfVariables, numberOfMinterms, minterms);
            }
            else
            {
                result = "0";
            }
            resultCalculated = true;
            resultButton(Bodyfont);
        }
        else if (CheckCollisionPointRec(mousePos, Reset))
        {
            visualizeKmap();
        }
    }
}

void Grid::listenHover()
{
    Vector2 mousePos = GetMousePosition();
    int x = mousePos.x;
    int y = mousePos.y;
    int col = (x - offsetX) / cellSize;
    int row = (y - offsetY) / cellSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else if (CheckCollisionPointRec(mousePos, Calculate))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        CalculateColor = CalculateColorHover;
    }
    else if (CheckCollisionPointRec(mousePos, Reset))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        ResetColor = ResetColorHover;
    }
    else
    {
        CalculateColor = {255, 248, 219, 255};
        ResetColor = {255, 248, 219, 255};
    }
}

void Grid::calculateButton(Font Bodyfont)
{
    int numberOfVariables = calculateNumberOfVariables(rows, cols);
    int rectOffsetX, rectOffsetY, rectHeight, rectWidth;
    rectOffsetX = offsetX;
    rectOffsetY = offsetY + gridHeight + 20;
    rectHeight = 50;
    rectWidth = (numberOfVariables != 2) ? (gridWidth / 2 - 10) : (gridWidth - 10);
    Calculate = {static_cast<float>(rectOffsetX),
                 static_cast<float>(rectOffsetY),
                 static_cast<float>(rectWidth),
                 static_cast<float>(rectHeight)};
    DrawRectangleRounded(Calculate, 0.1, 0, CalculateColor);
    int fontSize = (numberOfVariables == 5) ? 15 : 14;
    int textOffsetX, textOffsetY, textHeight, textWidth;
    textWidth = MeasureTextEx(Bodyfont, "Calculate", fontSize, 4).x;
    textHeight = MeasureTextEx(Bodyfont, "Calculate", fontSize, 4).y;
    textOffsetX = offsetX + (rectWidth - textWidth) / 2;
    textOffsetY = offsetY + gridHeight + 20 + (50 - textHeight) / 2;
    DrawTextEx(Bodyfont, "Calculate", Vector2{static_cast<float>(textOffsetX), static_cast<float>(textOffsetY)}, fontSize, 4, BLACK);
}

void Grid::visualizeButton(Font Bodyfont)
{
    int numberOfVariables = calculateNumberOfVariables(rows, cols);
    int rectOffsetX, rectOffsetY, rectHeight, rectWidth;
    rectOffsetX = (numberOfVariables != 2) ? (offsetX + (gridWidth / 2) + 10) : (offsetX);
    rectOffsetY = (numberOfVariables != 2) ? (offsetY + gridHeight + 20) : (offsetY + gridHeight + 90);
    rectHeight = 50;
    rectWidth = (numberOfVariables != 2) ? (gridWidth / 2 - 10) : (gridWidth - 10);
    Reset = {static_cast<float>(rectOffsetX),
             static_cast<float>(rectOffsetY),
             static_cast<float>(rectWidth),
             static_cast<float>(rectHeight)};
    DrawRectangleRounded(Reset, 0.1, 0, ResetColor);
    int textOffsetX, textOffsetY, textHeight, textWidth;
    textWidth = MeasureTextEx(Bodyfont, "Visualize", 15, 4).x;
    textHeight = MeasureTextEx(Bodyfont, "Visualize", 15, 4).y;
    textOffsetX = rectOffsetX + (rectWidth - textWidth) / 2;
    textOffsetY = rectOffsetY + (rectHeight - textHeight) / 2;
    DrawTextEx(Bodyfont, "Visualize", Vector2{static_cast<float>(textOffsetX), static_cast<float>(textOffsetY)}, 15, 4, BLACK);
}

void Grid::resultButton(Font Bodyfont)
{
    Vector2 resultWidth1 = MeasureTextEx(Bodyfont, result.c_str(), 22, 2);
    int resultWidth = resultWidth1.x;
    int rectWidth = resultWidth + 30;
    int offSetX = (GetScreenWidth() - rectWidth) / 2;
    int offSetY = (GetScreenHeight() - gridHeight) / 2 + gridHeight + 150;

    DrawRectangleRounded({static_cast<float>(offSetX), static_cast<float>(offSetY), static_cast<float>(rectWidth), 50}, 0.1, 0, WHITE);
    DrawTextEx(Bodyfont, "Result: ", Vector2{static_cast<float>(offSetX - 100), static_cast<float>(offSetY + (50 - 22) / 2)}, 22, 4, WHITE);
    printResult(offSetX, offSetY, resultWidth, resultWidth + 50, 50, Bodyfont);
}

void Grid::printResult(int ox, int oy, int rw, int rectWidth, int rectHeight, Font Bodyfont)
{
    DrawTextEx(Bodyfont, result.c_str(), Vector2{static_cast<float>(ox + 15), static_cast<float>(oy + (50 - 22) / 2)}, 22, 2, BLACK);
}

vector<int> Grid::returnMinterms()
{
    int twoVar[2][2] = {
        {0, 1},
        {2, 3}};
    int threeVar[2][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6}};
    int fourVar[4][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6},
        {12, 13, 15, 14},
        {8, 9, 11, 10}};
    int fiveVar[4][8] = {
        {0, 1, 3, 2, 6, 7, 5, 4},
        {8, 9, 11, 10, 14, 15, 13, 12},
        {24, 25, 27, 26, 30, 31, 29, 28},
        {16, 17, 19, 18, 22, 23, 21, 20}};

    vector<int> minterms;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (grid[row][col] == 1)
            {
                if (rows == 2 && cols == 2)
                {
                    minterms.push_back(twoVar[row][col]);
                }
                else if (rows == 2 && cols == 4)
                {
                    minterms.push_back(threeVar[row][col]);
                }
                else if (rows == 4 && cols == 4)
                {
                    minterms.push_back(fourVar[row][col]);
                }
                else if (rows == 4 && cols == 8)
                {
                    minterms.push_back(fiveVar[row][col]);
                }
            }
        }
    }
    sort(minterms.begin(), minterms.end());
    return minterms;
}

void Grid::SimulateLoading(float duration)
{
    float timeElapsed = 0.0f;
    const int screenWidth = 800;
    const int screenHeight = 600;

    while (timeElapsed < duration)
    {
        timeElapsed += GetFrameTime();
        float progress = timeElapsed / duration;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw loading text
        DrawText("Loading...", screenWidth / 2 - MeasureText("Loading...", 20) / 2, screenHeight / 2 - 50, 20, DARKGRAY);

        // Draw progress bar background
        DrawRectangle(screenWidth / 2 - 150, screenHeight / 2, 300, 30, LIGHTGRAY);

        // Draw progress bar
        DrawRectangle(screenWidth / 2 - 150, screenHeight / 2, 300 * progress, 30, DARKGRAY);

        // Draw progress percentage
        DrawText(TextFormat("%d%%", (int)(progress * 100)), screenWidth / 2 - MeasureText(TextFormat("%d%%", (int)(progress * 100)), 20) / 2, screenHeight / 2 + 5, 20, WHITE);

        EndDrawing();
    }
}

void performHttpRequest(string Uri, string body)
{
    string command = "powershell.exe -Command \"Invoke-WebRequest -Uri " + Uri + " -Method Post -Body '" + body + "' -OutFile './build/circuit.png' > $null\"";
    system(command.c_str());
}

void Grid::visualizeKmap()
{
    int numberOfVariables = calculateNumberOfVariables(rows, cols);
    // string Uri = "http://localhost:3000/solve" + to_string(numberOfVariables) + "var"; // For server hosted locally
    // string Uri = "https://k-map-visualizer.onrender.com/solve" + to_string(numberOfVariables) + "var"; // For server hosted on render
    string Uri = "https://k-map-visualizer-production.up.railway.app/solve" + to_string(numberOfVariables) + "var"; // For server hosted on railway
    minterms = returnMinterms();
    string body = "";
    for (auto i = 0; i < static_cast<int>(minterms.size()); i++)
    {
        body += (i == 0) ? "minterms[]=" : "&minterms[]=";
        body += to_string(minterms[i]);
    }
    // Start HTTP request in a separate thread
    promise<void> httpRequestPromise;
    future<void> httpRequestFuture = httpRequestPromise.get_future();

    thread httpRequestThread([&]()
                             {
                                 performHttpRequest(Uri, body);
                                 httpRequestPromise.set_value(); // Notify promise when done
                             });

    CloseWindow();
    const char *files = "./build/circuit.png";
    std::remove(files);
    string filename = "./build/circuit.png";
    const int screenWidth = 800;
    const int screenHeight = 600;
    Image icon = LoadImage("./assets/loading.png");
    InitWindow(screenWidth, screenHeight, "Loading...");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SimulateLoading(3.0f);
    while (true)
    {
        if (fs::exists(filename))
        {
            CloseWindow(); // Close the loading screen window
            InitWindow(800, 800, "Logic Circuit Visualization");
            Texture2D background = LoadTexture("./build/circuit.png");
            Image icon = LoadImage("./assets/logic.png");
            SetWindowSize(background.width, background.height);
            SetWindowIcon(icon);
            SetWindowPosition((GetMonitorWidth(0) - background.width) / 2, (GetMonitorHeight(0) - background.height) / 2);
            UnloadImage(icon);
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(background, 0, 0, WHITE);
                EndDrawing();
            }
            UnloadTexture(background);
            CloseWindow();
            break;
        }
    }
}

int Grid::calculateNumberOfVariables(int rows, int cols)
{
    int noOfCells = rows * cols;
    return log2(noOfCells);
}

string Grid::solveKMap(int numberOfVariables, int numberOfMinterms, vector<int> minterms)
{
    vector<string> primeImplicants = minimizeKMap(numberOfVariables, minterms);

    string minimizedExpression;
    for (size_t i = 0; i < primeImplicants.size(); ++i)
    {
        minimizedExpression += formatImplicant(primeImplicants[i], numberOfVariables);
        if (checkForXOR(minimizedExpression))
        {
            return minimizedExpression;
        }
        if (i < primeImplicants.size() - 1)
        {
            minimizedExpression += " + ";
        }
    }
    if (minimizedExpression.empty())
    {
        minimizedExpression = "1";
    }
    return minimizedExpression;
}

bool checkForXOR(string &minimizedExpression)
{
    if (minimizedExpression == "A XOR B")
    {
        minimizedExpression = "A XOR B";
        return true;
    }
    else if (minimizedExpression == "A XOR B XOR C")
    {
        minimizedExpression = "A XOR B XOR C";
        return true;
    }
    else if (minimizedExpression == "A XOR B XOR C XOR D")
    {
        minimizedExpression = "A XOR B XOR C XOR D";
        return true;
    }
    else if (minimizedExpression == "A XOR B XOR C XOR D XOR E")
    {
        minimizedExpression = "A XOR B XOR C XOR D XOR E";
        return true;
    }
    return false;
}
