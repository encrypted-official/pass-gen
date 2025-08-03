#include "screen.h"

typedef struct Option
{
    char text[32];
    Rectangle rec;
    Texture2D texture;
    bool isHovered;
} Option;

typedef struct SMState
{
    Rectangle menu_top;
    float menu_top_line_thickness;
    Option menu_top_option[6];
    Vector2 dragOffset;
    bool isDragging;
} SMState;

static SMState SM;

void ScreenMenuBarInit(void)
{
    SM.menu_top = (Rectangle){0.f, 0.f, GetScreenWidth(), GetScreenHeight() / 15.f};
    SM.menu_top_line_thickness = SM.menu_top.height / 15.f;
    SM.dragOffset = (Vector2){0.f, 0.f};
    SM.isDragging = false;

    strcpy(SM.menu_top_option[0].text, "Exit");
    SM.menu_top_option[0].rec = (Rectangle){
        SM.menu_top.width - (MeasureText(SM.menu_top_option[0].text, 20) + 25),
        0.f,
        MeasureText(SM.menu_top_option[0].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[0].isHovered = false;
    
    strcpy(SM.menu_top_option[1].text, "Max");
    SM.menu_top_option[1].rec = (Rectangle){
        SM.menu_top.width - (MeasureText(SM.menu_top_option[1].text, 20) + 25) - SM.menu_top_option[0].rec.width,
        0.f,
        MeasureText(SM.menu_top_option[1].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[1].isHovered = false;
    
    strcpy(SM.menu_top_option[2].text, "Min");
    SM.menu_top_option[2].rec = (Rectangle){
        SM.menu_top.width - (MeasureText(SM.menu_top_option[2].text, 20) + 25) - SM.menu_top_option[0].rec.width - SM.menu_top_option[1].rec.width,
        0.f,
        MeasureText(SM.menu_top_option[2].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[2].isHovered = false;
    
    strcpy(SM.menu_top_option[3].text, "Home");
    SM.menu_top_option[3].rec = (Rectangle){
        0.f,
        0.f,
        MeasureText(SM.menu_top_option[3].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[3].isHovered = false;
    
    strcpy(SM.menu_top_option[4].text, "File");
    SM.menu_top_option[4].rec = (Rectangle){
        SM.menu_top_option[3].rec.width,
        0.f,
        MeasureText(SM.menu_top_option[4].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[4].isHovered = false;

    strcpy(SM.menu_top_option[5].text, "Generate");
    SM.menu_top_option[5].rec = (Rectangle){
        SM.menu_top_option[3].rec.width + SM.menu_top_option[4].rec.width,
        0.f,
        MeasureText(SM.menu_top_option[5].text, 20) + 25,
        SM.menu_top.height - SM.menu_top_line_thickness
    };
    SM.menu_top_option[5].isHovered = false;
}

void ScreenMenuBarUpdate(void)
{
    Vector2 mousePos = GetMousePosition();

    if (!SM.isDragging &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        CheckCollisionPointRec(mousePos, (Rectangle){0.f, 0.f, GetScreenWidth(), GetScreenHeight()}))
    {
        SM.isDragging = true;
        SM.dragOffset = (Vector2){GetMouseX(), GetMouseY()};
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[0].rec))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            CloseWindow();
        }

        SM.menu_top_option[0].isHovered = true;
    }
    else
    {
        SM.menu_top_option[0].isHovered = false;
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[1].rec))
    {
        SM.menu_top_option[1].isHovered = true;
    }
    else
    {
        SM.menu_top_option[1].isHovered = false;
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[2].rec))
    {
        SM.menu_top_option[2].isHovered = true;
    }
    else
    {
        SM.menu_top_option[2].isHovered = false;
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[3].rec))
    {
        SM.menu_top_option[3].isHovered = true;
    }
    else
    {
        SM.menu_top_option[3].isHovered = false;
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[4].rec))
    {
        SM.menu_top_option[4].isHovered = true;
    }
    else
    {
        SM.menu_top_option[4].isHovered = false;
    }

    if (CheckCollisionPointRec(mousePos, SM.menu_top_option[5].rec))
    {
        SM.menu_top_option[5].isHovered = true;
    }
    else
    {
        SM.menu_top_option[5].isHovered = false;
    }

    if (SM.isDragging)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            SetWindowPosition(
                GetWindowPosition().x + GetMouseX() - SM.dragOffset.x,
                GetWindowPosition().y + GetMouseY() - SM.dragOffset.y
            );
        }
        else
        {
            SM.isDragging = false;
        }
    }
}

void ScreenMenuBarDraw(void)
{
    // ClearBackground((Color){18, 18, 18, 255});
    DrawRectangleRec(SM.menu_top, (Color){30, 30, 30, 255});

    DrawRectangleRec(
        SM.menu_top_option[0].rec,
        SM.menu_top_option[0].isHovered ? RED : (Color){30, 30, 30, 255}
    );

    DrawText(
        SM.menu_top_option[0].text,
        SM.menu_top.width - SM.menu_top_option[0].rec.width + ((SM.menu_top_option[0].rec.width - MeasureText(SM.menu_top_option[0].text, 20)) / 2.f),
        (SM.menu_top_option[0].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );
    
    DrawRectangleRec(
        SM.menu_top_option[1].rec,
        SM.menu_top_option[1].isHovered ? DARKGRAY : (Color){30, 30, 30, 255}
    );

    DrawText(
        SM.menu_top_option[1].text,
        SM.menu_top.width - SM.menu_top_option[1].rec.width + ((SM.menu_top_option[1].rec.width - MeasureText(SM.menu_top_option[1].text, 20)) / 2.f) - SM.menu_top_option[0].rec.width,
        (SM.menu_top_option[1].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );
    
    DrawRectangleRec(
        SM.menu_top_option[2].rec,
        SM.menu_top_option[2].isHovered ? DARKGRAY : (Color){30, 30, 30, 255}
    );

    DrawText(
        SM.menu_top_option[2].text,
        SM.menu_top.width - SM.menu_top_option[2].rec.width + ((SM.menu_top_option[2].rec.width - MeasureText(SM.menu_top_option[2].text, 20)) / 2.f) - SM.menu_top_option[0].rec.width - SM.menu_top_option[1].rec.width,
        (SM.menu_top_option[2].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );

    DrawRectangleRec(
        SM.menu_top_option[3].rec,
        SM.menu_top_option[3].isHovered ? (Color){45, 45, 45, 255} : (Color){30, 30, 30, 255}
    );
    
    DrawText(
        SM.menu_top_option[3].text,
        (SM.menu_top_option[3].rec.width - MeasureText(SM.menu_top_option[3].text, 20)) / 2.f,
        (SM.menu_top_option[3].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );

    DrawRectangleRec(
        SM.menu_top_option[4].rec,
        SM.menu_top_option[4].isHovered ? (Color){45, 45, 45, 255} : (Color){30, 30, 30, 255}
    );
    
    DrawText(
        SM.menu_top_option[4].text,
        (SM.menu_top_option[4].rec.width - MeasureText(SM.menu_top_option[4].text, 20)) / 2.f + SM.menu_top_option[3].rec.width,
        (SM.menu_top_option[4].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );

    DrawRectangleRec(
        SM.menu_top_option[5].rec,
        SM.menu_top_option[5].isHovered ? (Color){45, 45, 45, 255} : (Color){30, 30, 30, 255}
    );
    
    DrawText(
        SM.menu_top_option[5].text,
        (SM.menu_top_option[5].rec.width - MeasureText(SM.menu_top_option[5].text, 20)) / 2.f + SM.menu_top_option[3].rec.width + SM.menu_top_option[4].rec.width,
        (SM.menu_top_option[5].rec.height - 20) / 2.f,
        20,
        LIGHTGRAY
    );
 
    DrawLineEx(
        (Vector2){SM.menu_top.x, SM.menu_top.y + SM.menu_top.height - SM.menu_top_line_thickness / 2.f},
        (Vector2){SM.menu_top.x + SM.menu_top.width, SM.menu_top.y + SM.menu_top.height - SM.menu_top_line_thickness / 2.f},
        SM.menu_top_line_thickness,
        (Color){59, 59, 59, 255}
    );
}

void ScreenMenuBarUnload(void) {}