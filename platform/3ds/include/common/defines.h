#pragma once

#include <citro2d.h>
#include <3ds.h>

#define appletMainLoop aptMainLoop

#define romfsMountFromFsdev(path, offset, name)

#define MAX_GAMEPADS 1

#define JOYSTICK_MAX 150.0f

typedef struct _vibe {
    float amp_low;
    float amp_high;
    float freq_low;
    float freq_high;
} VibrationValue;

typedef circlePosition StickPosition;

typedef C3D_RenderTarget Renderer;

typedef C2D_Image Texture;

typedef struct _Frame Frame;

typedef C2D_Font FontHandle;
typedef C2D_TextBuf TextBuffer;
typedef C2D_Text TextHandle;

struct Color
{
    float r;
    float g;
    float b;
    float a = 1.0f;
};

struct Rect
{
    float x;
    float y;
    float width;
    float height;
};
