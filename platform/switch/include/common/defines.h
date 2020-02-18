#pragma once

#include <SDL.h>
#include <switch.h>

#define MAX_GAMEPADS 4

typedef SDL_Renderer Renderer;

typedef SDL_Window Frame;

typedef JoystickPosition StickPosition;

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} Color;
