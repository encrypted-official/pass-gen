#pragma once

#include "raylib.h"
#include "gui.h"
#include <string.h>

typedef void (*ScreenFunc)(void);

void ScreenMenuBarInit(void);
void ScreenMenuBarUpdate(void);
void ScreenMenuBarDraw(void);
void ScreenMenuBarUnload(void);

void ScreenHomeInit(void);
void ScreenHomeUpdate(void);
void ScreenHomeDraw(void);
void ScreenHomeUnload(void);

void ScreenFileInit(void);
void ScreenFileUpdate(void);
void ScreenFileDraw(void);
void ScreenFileUnload(void);

void ScreenGenerateInit(void);
void ScreenGenerateUpdate(void);
void ScreenGenerateDraw(void);
void ScreenGenerateUnload(void);

extern ScreenFunc screenInitFuncs[];
extern ScreenFunc screenUpdateFuncs[];
extern ScreenFunc screenDrawFuncs[];
extern ScreenFunc screenUnloadFuncs[];