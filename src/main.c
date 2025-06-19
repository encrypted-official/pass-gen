#include "gui.h"
#include "raylib.h"

int main(void)
{
    Gui_Init();
    
    while (!WindowShouldClose())
    {
        Gui_Update();
        Gui_Draw();
    }

    Gui_Unload();

    return 0;
}