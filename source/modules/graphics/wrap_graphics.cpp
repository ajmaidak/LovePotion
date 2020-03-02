#include "common/runtime.h"
#include "modules/graphics/wrap_graphics.h"

using namespace love;

#define instance() (Module::GetInstance<Graphics>(Module::M_GRAPHICS))

// int Wrap_Graphics::Rectangle(lua_State * L)
// {
//     const char * mode = luaL_checkstring(L, 1);
//     DrawMode drawMode = DrawMode::FILL;

//     if (!GetConstant(mode, drawMode))
//         return luaL_error(L, "Invalid draw mode %s", mode);

//     float x = luaL_optnumber(L, 2, 0);
//     float y = luaL_optnumber(L, 3, 0);

//     float width = luaL_checknumber(L, 4);
//     float height = luaL_checknumber(L, 5);

//     Render::Rectangle(mode, x, y, width, height, foreground);

//     return 0;
// }

int Wrap_Graphics::Clear(lua_State * L)
{
    Color clearColor = { 0, 0, 0, 1 };
    Color inputColor = clearColor;

    inputColor.r = luaL_checknumber(L, 1);
    inputColor.g = luaL_checknumber(L, 2);
    inputColor.b = luaL_checknumber(L, 3);

    instance()->AdjustColor(inputColor, &clearColor);

    auto windowModule = Module::GetInstance<Window>(Module::M_WINDOW);
    windowModule->Clear(&clearColor);

    return 0;
}

int Wrap_Graphics::Present(lua_State * L)
{
    auto windowModule = Module::GetInstance<Window>(Module::M_WINDOW);
    windowModule->Present();

    return 0;
}

int Wrap_Graphics::NewImage(lua_State * L)
{
    std::string path = luaL_checkstring(L, 1);

    Image * image = instance()->NewImage(path);

    Luax::PushType(L, image);

    image->Release();

    return 1;
}

int Wrap_Graphics::NewFont(lua_State * L)
{
    Font * font = nullptr;

    if (lua_isnumber(L, 1))
    {
        float size = luaL_checknumber(L, 1);

        font = instance()->NewFont(size);
    }
    else
    {
        std::string path = luaL_checkstring(L, 1);
        float size = luaL_optnumber(L, 2, Font::DEFAULT_SIZE);

        font = instance()->NewFont(path, size);
    }

    Luax::PushType(L, font);
    font->Release();

    return 1;
}

int Wrap_Graphics::Draw(lua_State * L)
{
    Image * image = Luax::CheckType<Image>(L, 1);
    int start = 2;

    float x = luaL_optnumber(L, start, 0);
    float y = luaL_optnumber(L, start + 1, 0);

    float r = luaL_optnumber(L, start + 2, 0);

    float sx = luaL_optnumber(L, start + 3, 1);
    float sy = luaL_optnumber(L, start + 4, 1);

    float ox = luaL_optnumber(L, start + 5, 0);
    float oy = luaL_optnumber(L, start + 6, 0);

    x += ox;
    y += oy;

    image->Draw(x, y, r, sx, sy);

    return 0;
}

int Wrap_Graphics::Print(lua_State * L)
{
    const char * text = luaL_checkstring(L, 1);

    float x = luaL_optnumber(L, 2, 0);
    float y = luaL_optnumber(L, 3, 0);

    Luax::CatchException(L, [&]() {
        instance()->Print(text, x, y);
    });

    return 0;
}

int Wrap_Graphics::SetNewFont(lua_State * L)
{
    int ret = Wrap_Graphics::NewFont(L);
    Font * font = Luax::CheckType<Font>(L, -1);

    instance()->SetFont(font);

    return ret;
}

int Wrap_Graphics::SetFont(lua_State * L)
{
    Font * font = Luax::CheckType<Font>(L, 1);

    instance()->SetFont(font);

    return 0;
}

int Wrap_Graphics::GetFont(lua_State * L)
{
    Font * font = nullptr;
    Luax::CatchException(L, [&]() {
        font = instance()->GetFont();
    });

    Luax::PushType(L, font);

    return 1;
}

int Wrap_Graphics::Reset(lua_State * L)
{
    instance()->Reset();

    return 0;
}

int Wrap_Graphics::GetBackgroundColor(lua_State * L)
{
    Color background = instance()->GetBackgroundColor();

    lua_pushnumber(L, background.r);
    lua_pushnumber(L, background.g);
    lua_pushnumber(L, background.b);

    return 3;
}

int Wrap_Graphics::SetBackgroundColor(lua_State * L)
{
    Color background = instance()->GetBackgroundColor();

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 3; i++)
            lua_rawgeti(L, 1, i);

        background.r = luaL_checknumber(L, -3);
        background.g = luaL_checknumber(L, -2);
        background.b = luaL_checknumber(L, -1);
    }
    else if (lua_isnumber(L, 1))
    {
        background.r = luaL_checknumber(L, 1);
        background.g = luaL_checknumber(L, 2);
        background.b = luaL_checknumber(L, 3);
    }

    instance()->SetBackgroundColor(background);

    return 0;
}

int Wrap_Graphics::GetColor(lua_State * L)
{
    Color foreground = instance()->GetColor();

    lua_pushnumber(L, foreground.r);
    lua_pushnumber(L, foreground.g);
    lua_pushnumber(L, foreground.b);
    lua_pushnumber(L, foreground.a);

    return 4;
}

int Wrap_Graphics::SetColor(lua_State * L)
{
    Color foreground = instance()->GetColor();

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 4; i++)
            lua_rawgeti(L, 1, i);

        foreground.r = luaL_checknumber(L, -4);
        foreground.g = luaL_checknumber(L, -3);
        foreground.b = luaL_checknumber(L, -2);
        foreground.a = luaL_optnumber(L, -1, 1);
    }
    else if (lua_isnumber(L, 1))
    {
        foreground.r = luaL_checknumber(L, 1);
        foreground.g = luaL_checknumber(L, 2);
        foreground.b = luaL_checknumber(L, 3);
        foreground.a = luaL_optnumber(L, 4, 1);
    }

    instance()->SetColor(foreground);

    return 0;
}

int Wrap_Graphics::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "clear",              Clear              },
        { "draw",               Draw               },
        { "getBackgroundColor", GetBackgroundColor },
        { "getColor",           GetColor           },
        { "newImage",           NewImage           },
        { "present",            Present            },
        // { "rectangle",          Rectangle          },
        { "setBackgroundColor", SetBackgroundColor },
        { "setColor",           SetColor           },
        { "newFont",            NewFont            },
        { "setNewFont",         SetNewFont         },
        { "print",              Print              },
        { "reset",              Reset              },
        { 0,                    0                  }
    };

    lua_CFunction types[] =
    {
        Wrap_Image::Register,
        Wrap_Font::Register,
        0
    };

    Graphics * instance = instance();

    if (instance == nullptr)
        Luax::CatchException(L, [&]() { instance = new Graphics(); });
    else
        instance->Retain();

    WrappedModule module;

    module.instance = instance;
    module.name = "graphics";
    module.functions = reg;
    module.type = &Module::type;
    module.types = types;

    return Luax::RegisterModule(L, module);
}
