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

// custom structs
struct Module
{
    const char * name;
    const luaL_reg * functions;
};

// std stuff
#include <algorithm>
#include <array>
#include <math.h>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "common/defines.h"

#include "common/logger.h"
#include "common/luax.h"
#include "common/variant.h"
#include "common/message.h"
