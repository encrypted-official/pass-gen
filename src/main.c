#include "raylib.h"

int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_Encrypted's Password Generator");

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}