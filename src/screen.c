#include "screen.h"
#include "raylib.h"

typedef struct StartMenuState
{
    Texture2D background;
    Texture2D button_primary;
    Texture2D button_secondary;
    Rectangle buttonGenerator;
    Rectangle button_normal_rect;
    Vector2 button_dim_hovered;

} StartMenuState;

typedef struct ToggleOption {
    const char *toggled_text;
    const char *untoggled_text;
    Rectangle rect;
    bool flag;
    bool isHovered;

} ToggleOption;

typedef struct GeneratorState
{
    Font font[2];
    Texture2D background;
    Rectangle section_toggleables;
    ToggleOption toggle_option[4];

} GeneratorState;

static StartMenuState startMenu;
static GeneratorState generatorScreen;

void Screen_StartMenu_Init(void)
{
    startMenu.background = LoadTexture("assets/textures/background_1.png");
    startMenu.button_primary = LoadTexture("assets/textures/button_1.png");
    startMenu.button_secondary = LoadTexture("assets/textures/button_2.png");
    startMenu.buttonGenerator = (Rectangle){ (GetScreenWidth() - 250) / 2, (GetScreenHeight() - 75) / 2, 250, 75 };
    startMenu.button_normal_rect = (Rectangle){ 50.0f, 200.0f, 200.0f, 50.0f };
}

void Screen_StartMenu_Update(void)
{
    if (CheckCollisionPointRec(GetMousePosition(), startMenu.button_normal_rect) &&
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
    generatorScreen.font[0] = LoadFontEx("assets/fonts/Arvo/Arvo-Regular.ttf", 128, 0, 0);
    SetTextureFilter(generatorScreen.font[0].texture, TEXTURE_FILTER_TRILINEAR);

    generatorScreen.font[1] = LoadFontEx("assets/fonts/Arvo/Arvo-Bold.ttf", 128, 0, 0);
    SetTextureFilter(generatorScreen.font[1].texture, TEXTURE_FILTER_TRILINEAR);

    generatorScreen.background = LoadTexture("assets/textures/background_1.png");

    generatorScreen.section_toggleables = (Rectangle){ 55, 265, 340, 250 };

    generatorScreen.toggle_option[0].toggled_text = "[x] Uppercase (A-Z)";
    generatorScreen.toggle_option[0].untoggled_text = "[  ] Uppercase (A-Z)";
    generatorScreen.toggle_option[0].rect = (Rectangle){ 85, 300, 250, 30 };
    generatorScreen.toggle_option[0].flag = true;
    
    generatorScreen.toggle_option[1].toggled_text = "[x] Lowercase (a-z)";
    generatorScreen.toggle_option[1].untoggled_text = "[  ] Lowercase (a-z)";
    generatorScreen.toggle_option[1].rect = (Rectangle){ 85, 350, 247.5f, 30 };
    generatorScreen.toggle_option[1].flag = true;

    generatorScreen.toggle_option[2].toggled_text = "[x] Numbers (0-9)";
    generatorScreen.toggle_option[2].untoggled_text = "[  ] Numbers (0-9)";
    generatorScreen.toggle_option[2].rect = (Rectangle){ 85, 400, 225, 30 };
    generatorScreen.toggle_option[2].flag = false;

    generatorScreen.toggle_option[3].toggled_text = "[x] Symbols";
    generatorScreen.toggle_option[3].untoggled_text = "[  ] Symbols";
    generatorScreen.toggle_option[3].rect = (Rectangle){ 85, 450, 150, 30 };
    generatorScreen.toggle_option[3].flag = false;
}

void Screen_Generator_Update(void)
{
    for (int i = 0; i < 4; ++i)
    {
        generatorScreen.toggle_option[i].isHovered = false;

        if (CheckCollisionPointRec(GetMousePosition(), generatorScreen.toggle_option[i].rect))
        {
            generatorScreen.toggle_option[i].isHovered = true;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                bool isAtleastOneOptionToggledExceptClicked = false;

                for (int j = 0; j < 4; ++j)
                {
                    if (i != j && generatorScreen.toggle_option[j].flag)
                    {
                        isAtleastOneOptionToggledExceptClicked = true;
                        break;
                    }
                }

                if (isAtleastOneOptionToggledExceptClicked)
                {
                    generatorScreen.toggle_option[i].flag = !generatorScreen.toggle_option[i].flag;
                }
            }
        }
    }
}

void Screen_Generator_Draw(void)
{
    // ClearBackground((Color){ 55, 55, 55, 255 });
    ClearBackground((Color){ 235, 235, 235, 255 });
    // DrawTexture(startMenu.background, 0, 0, (Color){ 55, 55, 55, 100 });
    
    DrawRectangleRounded((Rectangle) { generatorScreen.section_toggleables.x - 10,
                                        generatorScreen.section_toggleables.y - 10,
                                        generatorScreen.section_toggleables.width + 2 * 10,
                                        generatorScreen.section_toggleables.height + 2 * 10 }, 0.1f, 16, (Color){ 200, 200, 200, 255 });

    DrawRectangleRounded(generatorScreen.section_toggleables, 0.1f, 16, (Color){ 245, 245, 245, 255 });

    for (int i = 0; i < 4; ++i)
    {   
        // DrawRectangleRec(generatorScreen.toggle_option[i].rect, generatorScreen.toggle_option[i].flag ? DARKGREEN : MAROON);
        
        DrawTextEx(generatorScreen.font[1],
                generatorScreen.toggle_option[i].flag ? generatorScreen.toggle_option[i].toggled_text : generatorScreen.toggle_option[i].untoggled_text,
                (Vector2){ generatorScreen.toggle_option[i].rect.x, generatorScreen.toggle_option[i].rect.y},
                generatorScreen.toggle_option[i].isHovered ? 28 : 26,
                1.5f,
                generatorScreen.toggle_option[i].isHovered ? (Color){ 30, 30, 30, 255 } : (generatorScreen.toggle_option[i].flag ? (Color){ 33, 150, 243, 255 } : (Color){ 130, 130, 130, 150 }));
    }
}

void Screen_Generator_Unload(void)
{
    UnloadFont(generatorScreen.font[0]);
    UnloadFont(generatorScreen.font[1]);
    UnloadTexture(generatorScreen.background);
}