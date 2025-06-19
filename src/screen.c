#include "screen.h"
#include "raylib.h"

typedef struct StartMenuState
{
    Texture2D background;
    Texture2D button_primary;
    Texture2D button_secondary;
    Rectangle buttonGenerator;
    Rectangle button_normal_rec;
    Vector2 button_dim_hovered;
} StartMenuState;

static StartMenuState startMenu;

void Screen_StartMenu_Init(void)
{
    startMenu.background = LoadTexture("assets/textures/background_1.png");
    startMenu.button_primary = LoadTexture("assets/textures/button_1.png");
    startMenu.button_secondary = LoadTexture("assets/textures/button_2.png");
    startMenu.buttonGenerator = (Rectangle){ (GetScreenWidth() - 250) / 2, (GetScreenHeight() - 75) / 2, 250, 75 };
    startMenu.button_normal_rec = (Rectangle){ 50.0f, 200.0f, 200.0f, 50.0f };
}

void Screen_StartMenu_Update(void)
{
    if (CheckCollisionPointRec(GetMousePosition(), startMenu.button_normal_rec) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Screen_StartMenu_Unload();
        // Screen_Generator_Init();
    }
}

void Screen_StartMenu_Draw(void)
{
    ClearBackground((Color){ 55, 55, 55, 255 });

    DrawTexture(startMenu.background, 0, 0, (Color){ 55, 55, 55, 100 });
    // DrawTexturePro(startMenu.button_primary,
    //     (Rectangle){ 0, 0, startMenu.button_primary.width, startMenu.button_primary.height },
    //     (Rectangle){ startMenu.button_normal_rec.x, startMenu.button_normal_rec.y, startMenu.button_normal_rec.width, startMenu.button_normal_rec.height },
    //     (Vector2){0, 0},
    //     0.0f,
    //     WHITE);
}

void Screen_StartMenu_Unload(void)
{
    UnloadTexture(startMenu.background);
}

void Screen_Generator_Init(void)
{
    return;
}

void Screen_Generator_Update(void);
void Screen_Generator_Draw(void);
void Screen_Generator_Unload(void);