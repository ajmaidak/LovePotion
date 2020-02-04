#pragma once

#include <citro2d.h>
#include <3ds.h>

#define appletMainLoop aptMainLoop

#define romfsMountFromFsdev(path, offset, name)

typedef circlePosition StickPosition;

typedef C3D_RenderTarget Renderer;

typedef struct _Frame Frame;

struct Color
{
    float r;
    float g;
    float b;
    float a = 1.0f;
};
