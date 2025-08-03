#pragma once

typedef enum GuiType
{
    HOME = 0,
    FILE,
    GENERATE
} GuiType;

void GuiInit(void);
void GuiUpdate(void);
void GuiDraw(void);
void GuiUnload(void);