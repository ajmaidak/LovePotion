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

#if defined (_3DS)
    #include "common/defines.h"
#elif defined (__SWITCH__)
    #include "common/defines.h"
#endif

#include "common/logger.h"

// std stuff
#include <string>
