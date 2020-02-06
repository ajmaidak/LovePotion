#include "common/runtime.h"

std::string Variant::GetTypeString() const
{
    Type type = (Type)this->index();

    if (type == Type::BOOLEAN)
        return "boolean";
    else if (type == Type::NIL)
        return "nil";
    else if (type == Type::NUMBER)
        return "number";
    else if (type == Type::STRING)
        return "string";
    else if (type == Type::LOVE_OBJECT)
        return "object";

    return "unknown";
}

Variant::Type Variant::GetType() const
{
    Type retval = (Type)this->index();

    return retval;
}

Variant Variant::FromLua(lua_State * L, int n)
{
    std::string string;
    bool boolean;
    float number;

    Variant retval;

    if (n < 0)
        n += lua_gettop(L) + 1;

    switch (lua_type(L, n))
    {
        case LUA_TSTRING:
            string = lua_tostring(L, n);
            retval.emplace<Type::STRING>(string);
            return retval;
        case LUA_TNIL:
            retval.emplace<Type::NIL>(Nil());
            return retval;
        case LUA_TBOOLEAN:
            boolean = lua_toboolean(L, n);
            retval.emplace<Type::BOOLEAN>(boolean);
            return retval;
        case LUA_TNUMBER:
            number = lua_tonumber(L, n);
            retval.emplace<Type::NUMBER>(number);
            return retval;

        break;
    }

    retval.emplace<Type::UNKNOWN>(std::monostate {});
    return retval;
}

void Variant::ToLua(lua_State * L) const
{
    std::string string;
    void * love_object;
    bool boolean;
    float number;

    switch (this->GetType())
    {
        case Type::STRING:
            string = std::get<(size_t)Type::STRING>(*this);
            lua_pushlstring(L, string.c_str(), string.length());
            break;
        case Type::LOVE_OBJECT:
            love_object = std::get<(size_t)Type::LOVE_OBJECT>(*this);
            Luax::PushObject(L, love_object);
            break;
        case Type::BOOLEAN:
            boolean = std::get<(size_t)Type::BOOLEAN>(*this);
            lua_pushboolean(L, boolean);
            break;
        case Type::NUMBER:
            number = std::get<(size_t)Type::NUMBER>(*this);
            lua_pushnumber(L, number);
            break;
        case Type::NIL:
        default:
            lua_pushnil(L);
            break;
    }
}
