#include "screen.h"
#include <string.h>
#include "raylib.h"
#include "sodium.h"

typedef struct StartMenuState
{
    Texture2D background;
    Texture2D button_primary;
    Texture2D button_secondary;
    Rectangle buttonGenerator;
    Rectangle button_normal_rect;
    Vector2 button_dim_hovered;

} StartMenuState;

static StartMenuState startMenu;

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

    }
}

void Screen_StartMenu_Draw(void)
{
    ClearBackground((Color){ 55, 55, 55, 255 });

    DrawTexture(startMenu.background, 0, 0, (Color){ 55, 55, 55, 100 });
}

void Screen_StartMenu_Unload(void)
{
    UnloadTexture(startMenu.background);
}

typedef struct ToggleOption
{
    const char *charset;
    const char *toggled_text;
    const char *untoggled_text;
    Rectangle rect;
    bool flag;
    bool isHovered;

} ToggleOption;

typedef struct Password
{
    char pass[256];
    int len;

} Password;

typedef struct GeneratorState
{
    Font font[2];
    Texture2D background;
    Rectangle section_password;
    Rectangle section_toggleables;
    Rectangle button_regen;
    Rectangle button_copy;
    ToggleOption toggle_option[4];
    Password current_password;

} GeneratorState;

static GeneratorState generatorScreen;

void RegeneratePassword(void)
{
    char final_charset[256] = {0};
    memset(generatorScreen.current_password.pass, 0, sizeof(generatorScreen.current_password.pass));

    for (int i = 0; i < 4; ++i)
    {
        if (generatorScreen.toggle_option[i].flag)
        {
            strncat(final_charset, generatorScreen.toggle_option[i].charset, sizeof(final_charset) - strlen(final_charset) - 1);     
        }
    }

    int final_charset_size = strlen(final_charset);

    for (int i = 0; i < generatorScreen.current_password.len; ++i)
    {
        unsigned int index = randombytes_uniform(final_charset_size);
        generatorScreen.current_password.pass[i] += final_charset[index];
    }
}

void DrawPassText(void)
{
    int font_size = 32;

    DrawTextEx(generatorScreen.font[1],
            generatorScreen.current_password.pass,
            (Vector2){ generatorScreen.section_password.x + (generatorScreen.section_password.width - MeasureText(generatorScreen.current_password.pass, font_size)) / 2,
                    generatorScreen.section_password.y + (generatorScreen.section_password.height - font_size) / 2 },
            font_size,
            1.5f,
            WHITE);
}

void Screen_Generator_Init(void)
{
    if (sodium_init() < 0)
    {
        exit(1);
    }

    // generatorScreen.font[0] = LoadFontEx("assets/fonts/Arvo/Arvo-Regular.ttf", 128, 0, 0);
    // SetTextureFilter(generatorScreen.font[0].texture, TEXTURE_FILTER_TRILINEAR);

    generatorScreen.font[1] = LoadFontEx("assets/fonts/Arvo/Arvo-Bold.ttf", 128, 0, 0);
    SetTextureFilter(generatorScreen.font[1].texture, TEXTURE_FILTER_TRILINEAR);

    // generatorScreen.background = LoadTexture("assets/textures/background_1.png");

    generatorScreen.section_password = (Rectangle){ 55, 75, 790, 75 };
    generatorScreen.section_toggleables = (Rectangle){ 55, 285, 340, 250 };
    generatorScreen.button_regen = (Rectangle){ (55 + 790) - 400, (285 + 250) - 250, 200, 100 };
    generatorScreen.button_copy = (Rectangle){ (55 + 790) - 400, (285 + 250) - 100, 400, 100 };

    generatorScreen.toggle_option[0].charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    generatorScreen.toggle_option[0].toggled_text = "[x] Uppercase (A-Z)";
    generatorScreen.toggle_option[0].untoggled_text = "[  ] Uppercase (A-Z)";
    generatorScreen.toggle_option[0].rect = (Rectangle){ 85, 320, 250, 30 };
    generatorScreen.toggle_option[0].flag = true;
    
    generatorScreen.toggle_option[1].charset = "abcdefghijklmnopqrstuvwxyz";
    generatorScreen.toggle_option[1].toggled_text = "[x] Lowercase (a-z)";
    generatorScreen.toggle_option[1].untoggled_text = "[  ] Lowercase (a-z)";
    generatorScreen.toggle_option[1].rect = (Rectangle){ 85, 370, 247.5f, 30 };
    generatorScreen.toggle_option[1].flag = true;

    generatorScreen.toggle_option[2].charset = "0123456789";
    generatorScreen.toggle_option[2].toggled_text = "[x] Numbers (0-9)";
    generatorScreen.toggle_option[2].untoggled_text = "[  ] Numbers (0-9)";
    generatorScreen.toggle_option[2].rect = (Rectangle){ 85, 420, 225, 30 };
    generatorScreen.toggle_option[2].flag = false;

    generatorScreen.toggle_option[3].charset = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    generatorScreen.toggle_option[3].toggled_text = "[x] Symbols";
    generatorScreen.toggle_option[3].untoggled_text = "[  ] Symbols";
    generatorScreen.toggle_option[3].rect = (Rectangle){ 85, 470, 150, 30 };
    generatorScreen.toggle_option[3].flag = false;

    generatorScreen.current_password.len = 22;
    RegeneratePassword();
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
                    RegeneratePassword();
                }
            }
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), generatorScreen.button_regen))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            RegeneratePassword();   
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), generatorScreen.button_copy))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            SetClipboardText(generatorScreen.current_password.pass);
        }
    }
}

void Screen_Generator_Draw(void)
{
    // ClearBackground((Color){ 55, 55, 55, 255 });
    ClearBackground(BLACK);
    // DrawTexture(startMenu.background, 0, 0, (Color){ 55, 55, 55, 100 });

    DrawRectangleRounded((Rectangle) { generatorScreen.section_password.x - 10,
                                        generatorScreen.section_password.y - 10,
                                        generatorScreen.section_password.width + 2 * 10,
                                        generatorScreen.section_password.height + 2 * 10 }, 0.1f, 16, (Color){ 152, 251, 152, 255 });

    DrawRectangleRounded(generatorScreen.section_password, 0.1f, 16, (Color){ 45, 45, 45, 255 });
    
    DrawRectangleRounded((Rectangle) { generatorScreen.section_toggleables.x - 10,
                                        generatorScreen.section_toggleables.y - 10,
                                        generatorScreen.section_toggleables.width + 2 * 10,
                                        generatorScreen.section_toggleables.height + 2 * 10 }, 0.05f, 16, (Color){ 45, 45, 45, 200 });

    // DrawRectangleRounded(generatorScreen.section_toggleables, 0.05f, 16, (Color){ 62, 62, 62, 200 });
    
    DrawRectangleRounded((Rectangle) { generatorScreen.button_regen.x - 10,
                                        generatorScreen.button_regen.y - 10,
                                        generatorScreen.button_regen.width + 2 * 10,
                                        generatorScreen.button_regen.height + 2 * 10 }, 0.1f, 16, (Color){ 45, 45, 45, 200 });
    DrawRectangleRounded(generatorScreen.button_regen, 0.1f, 16, BLACK);

    Vector2 temp_size = MeasureTextEx(generatorScreen.font[1], "REGENERATE", 24, 1.5f);
    DrawTextEx(generatorScreen.font[1],
            "REGENERATE",
            (Vector2){ generatorScreen.button_regen.x + (generatorScreen.button_regen.width - temp_size.x) / 2,
                    generatorScreen.button_regen.y + (generatorScreen.button_regen.height - temp_size.y) / 2 },
            24,
            1.5f,
            WHITE);
    
    DrawRectangleRounded((Rectangle) { generatorScreen.button_copy.x - 10,
                                        generatorScreen.button_copy.y - 10,
                                        generatorScreen.button_copy.width + 2 * 10,
                                        generatorScreen.button_copy.height + 2 * 10 }, 0.1f, 16, (Color){ 45, 45, 45, 200 });

    DrawRectangleRounded(generatorScreen.button_copy, 0.1f, 16, BLACK);

    temp_size = MeasureTextEx(generatorScreen.font[1], "COPY", 52, 2.0f);
    DrawTextEx(generatorScreen.font[1],
            "COPY",
            (Vector2){ generatorScreen.button_copy.x + (generatorScreen.button_copy.width - temp_size.x) / 2,
                    generatorScreen.button_copy.y + (generatorScreen.button_copy.height - temp_size.y) / 2 },
            52,
            2.0f,
            (Color){ 33, 150, 243, 255 });

    DrawPassText();

    for (int i = 0; i < 4; ++i)
    {   
        DrawTextEx(generatorScreen.font[1],
                generatorScreen.toggle_option[i].flag ? generatorScreen.toggle_option[i].toggled_text : generatorScreen.toggle_option[i].untoggled_text,
                (Vector2){ generatorScreen.toggle_option[i].rect.x, generatorScreen.toggle_option[i].rect.y},
                generatorScreen.toggle_option[i].isHovered ? 28 : 26,
                1.5f,
                generatorScreen.toggle_option[i].isHovered ? RAYWHITE : (generatorScreen.toggle_option[i].flag ? (Color){ 33, 150, 243, 255 } : (Color){ 130, 130, 130, 150 }));
    }
}

void Screen_Generator_Unload(void)
{
    // UnloadFont(generatorScreen.font[0]);
    UnloadFont(generatorScreen.font[1]);
    // UnloadTexture(generatorScreen.background);
}