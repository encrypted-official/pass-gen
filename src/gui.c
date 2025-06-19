#include "gui.h"
#include "screen.h"
#include "raylib.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int FRAMES_PER_SECOND = 144;

void Gui_Init(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_Encrypted's Password Generator");
    SetTargetFPS(FRAMES_PER_SECOND);

    Screen_StartMenu_Init();
}

void Gui_Update(void)
{
    Screen_StartMenu_Update();
}

void Gui_Draw(void)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        Screen_StartMenu_Draw();
    EndDrawing();
}

void Gui_Unload(void)
{
    CloseWindow();
}