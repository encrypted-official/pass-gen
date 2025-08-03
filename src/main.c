#include "gui.h"
#include "raylib.h"

int main(void)
{
    GuiInit();
    
    while (!WindowShouldClose())
    {
        GuiUpdate();
        GuiDraw();
    }

    GuiUnload();

    return 0;
}