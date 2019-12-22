#pragma once

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    #include <compat-5.3.h>
    #include <luaobj.h>

    #include <lutf8lib.h>
}

struct WrappedModule
{
    const char * name;
    const luaL_reg * functions;
};

#include "common/defines.h"

#include "common/logger.h"
#include "common/luax.h"

// std stuff
#include <string>
#include <math.h>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
