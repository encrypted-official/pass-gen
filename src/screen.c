#include "screen.h"

ScreenFunc screenInitFuncs[] =
{
    ScreenHomeInit,
    ScreenFileInit,
    ScreenGenerateInit,
};

ScreenFunc screenUpdateFuncs[] =
{
    ScreenHomeUpdate,
    ScreenFileUpdate,
    ScreenGenerateUpdate,
};

ScreenFunc screenDrawFuncs[] =
{
    ScreenHomeDraw,
    ScreenFileDraw,
    ScreenGenerateDraw,
};

ScreenFunc screenUnloadFuncs[] =
{
    ScreenHomeUnload,
    ScreenFileUnload,
    ScreenGenerateUnload,
};
