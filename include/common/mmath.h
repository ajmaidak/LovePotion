#pragma once

#include <cstdlib> // for rand() and RAND_MAX

namespace love
{
    struct Rect
    {
        int x, y;
        int w, h;

        bool operator == (const Rect & rhs) const
        {
            return x == rhs.x && y == rhs.y && w == rhs.w && h == rhs.h;
        }
    };
}
