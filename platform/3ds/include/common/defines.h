#pragma once

#include <citro2d.h>
#include <3ds.h>

#define appletMainLoop aptMainLoop

#define romfsMountFromFsdev(path, offset, name)

typedef C3D_RenderTarget Renderer;

typedef struct
{
    int open;
} Frame;

typedef struct
{
    float r;
    float g;
    float b;
    float a = 1.0f;
} Color;
