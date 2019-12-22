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

#include "common/defines.h"

#include "common/logger.h"
#include "common/laux.h"

// std stuff
#include <string>
#include <math.h>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
