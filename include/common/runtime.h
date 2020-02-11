#pragma once

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    #include <compat-5.3.h>
    #include <lutf8lib.h>
}

// custom structs
struct Module
{
    const char * name;
    const luaL_reg * functions;
    const lua_CFunction * types;
};

struct Nil {};

enum DoneAction
{
    DONE_QUIT
};

// std stuff
#include <algorithm>
#include <array>
#include <math.h>
#include <queue>
#include <map>
#include <atomic>
#include <bitset>

#include <string>
using namespace std::string_literals;

#include <utility>
#include <vector>
#include <variant>

#include "common/strongref.h"
#include "common/type.h"
#include "common/defines.h"
#include "common/proxy.h"

#include "common/logger.h"
#include "common/luax.h"

#include "common/variant.h"
#include "common/message.h"
