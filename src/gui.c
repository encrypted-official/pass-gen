#include "gui.h"
#include "screen.h"
#include "raylib.h"

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 700;

GuiType currentGui = HOME;

void GuiInit(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_Encrypted's Password Generator");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    screenInitFuncs[currentGui]();
    ScreenMenuBarInit();
}

void GuiUpdate(void)
{
    screenUpdateFuncs[currentGui]();
    ScreenMenuBarUpdate();
}

void GuiDraw(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    screenDrawFuncs[currentGui]();
    ScreenMenuBarDraw();

    EndDrawing();
}

void GuiUnload(void)
{
    screenUnloadFuncs[currentGui]();
    ScreenMenuBarUnload();

    CloseWindow();
}