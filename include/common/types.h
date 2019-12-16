#pragma once

#include <string>
#include <vector>

#if defined (_3DS)
    #include <3ds.h>
#elif defined (__SWITCH__)
    #include <switch.h>
#endif

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct
{
    double ox;
    double oy;

    double r;

    double sx;
    double sy;

    double kx;
    double ky;
} StackMatrix;

typedef enum
{
    BOOLEAN,
    LUSERDATA,
    NIL,
    NUMBER,
    STRING,
    TABLE,
    UNKNOWN,
    USERDATA
} VARIANTS;

typedef enum
{
    OBJECTS
} REGISTRY;

typedef struct
{
    char * buffer;
    char ip[0x40];
    int * port;
} Packet;

typedef struct
{
    u32 host;
    u16 port;
} IPAddress;

typedef struct
{
    int x;
    int y;
    int width;
    int height;

    int atlasWidth;
    int atlasHeight;
} Viewport;

typedef struct
{
    char * buffer;
    size_t size;
    int code;
    char * header;
} HTTPChunk;

extern std::vector<const char *> FILE_MODES;

extern std::vector<const char *> SOURCE_TYPES;

extern std::vector<const char *> DRAW_MODES;

extern std::vector<const char *> KEYBOARD_TYPES;