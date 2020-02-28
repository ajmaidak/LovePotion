#include "common/runtime.h"

using namespace love;

Proxy * Variant::TryExtractProxy(lua_State * L, size_t index)
{
    Proxy * proxy = (Proxy *)lua_touserdata(L, index);

    if (!proxy || !proxy->type)
        return nullptr;

    if (dynamic_cast<Object *>(proxy->object) != nullptr)
        return proxy;

    return nullptr;
}

Variant::~Variant()
{
    Type self = this->GetType();
    Proxy selfProxy;

    if (self == Type::LOVE_OBJECT)
    {
        selfProxy = std::get<(size_t)Type::LOVE_OBJECT>(*this);

        if (selfProxy.object != nullptr)
            selfProxy.object->Release();
    }
}

Variant & Variant::operator=(const Variant & v)
{
    Type other = v.GetType();

    Proxy otherProxy;
    if (other == Type::LOVE_OBJECT)
    {
        otherProxy = std::get<(size_t)Type::LOVE_OBJECT>(*this);
        otherProxy.object->Retain();
    }

    Type self = this->GetType();
    Proxy selfProxy;

    if (self == Type::LOVE_OBJECT)
    {
        selfProxy = std::get<(size_t)Type::LOVE_OBJECT>(*this);
        selfProxy.object->Release();
    }

    std::variant<std::monostate, bool, Proxy, void *, Nil, float, std::string>::operator=(std::forward<const Variant &>(v));

    return *this;
}

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
    else if (type == Type::LUSERDATA)
        return "light userdata";

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
    Proxy proxy;
    bool boolean;
    float number;
    void * lightUserdata;

    switch (this->GetType())
    {
        case Type::STRING:
            string = std::get<(size_t)Type::STRING>(*this);
            lua_pushlstring(L, string.c_str(), string.length());
            break;
        case Type::LOVE_OBJECT:
            proxy = std::get<(size_t)Type::LOVE_OBJECT>(*this);
            Luax::PushType(L, *proxy.type, proxy.object);
            break;
        case Type::BOOLEAN:
            boolean = std::get<(size_t)Type::BOOLEAN>(*this);
            lua_pushboolean(L, boolean);
            break;
        case Type::NUMBER:
            number = std::get<(size_t)Type::NUMBER>(*this);
            lua_pushnumber(L, number);
            break;
        case Type::LUSERDATA:
            lightUserdata = std::get<(size_t)Type::LUSERDATA>(*this);
            lua_pushlightuserdata(L, lightUserdata);
        case Type::NIL:
        default:
            lua_pushnil(L);
            break;
    }
}
