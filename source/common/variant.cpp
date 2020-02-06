#include "common/runtime.h"
#include "common/variant.h"

Variant::Variant()
{
    this->type = Type::NIL;
}

Variant::Variant(const char * string, size_t length)
{
    if (length <= MAX_SMALL_STR_LENGTH)
    {
        this->type = Type::SMALL_STRING;
        memcpy(data.smallString.string, string, length);
        data.smallString.length = (u8)length;
    }
    else
    {
        this->type = Type::STRING;

        char * str = new char[length + 1];
        str[length] = '\0';

        memcpy(str, this->data.string, length);
    }
}

Variant::Variant(float number)
{
    this->type = Type::NUMBER;
    this->data.number = number;
}

Variant::Variant(bool boolean)
{
    this->type = Type::BOOLEAN;
    this->data.boolean = boolean;
}

Variant::Variant(void * lightuserdata_key)
{
    this->type = Type::LOVE_OBJECT;
    this->data.loveObject = lightuserdata_key;
}

Variant::Variant(const std::string & string) : Variant(string.c_str(), string.length())
{
}

Variant::Variant(Variant && v) : type(std::move(v.type)), data(std::move(v.data))
{
    v.type = Type::NIL;
}

Variant::Variant(const Variant & v) : type(v.type), data(v.data)
{
}

Variant & Variant::operator = (const Variant & v)
{
    if (this->type == Type::STRING)
        delete[] this->data.string;

    this->type = v.type;
    this->data = v.data;

    return *this;
}

Variant::~Variant()
{
    if (this->type == Type::STRING)
        delete[] this->data.string;

}

Variant Variant::FromLua(lua_State * L, int n)
{
    size_t length;
    const char * string;
    bool boolean;
    float number;

    if (n < 0)
        n += lua_gettop(L) + 1;

    switch (lua_type(L, n))
    {
        case LUA_TSTRING:
            string = lua_tolstring(L, n, &length);
            return Variant(string, length);
        case LUA_TNIL:
            return Variant();
        case LUA_TBOOLEAN:
            boolean = lua_toboolean(L, n);
            return Variant(boolean);
        case LUA_TNUMBER:
            number = lua_tonumber(L, n);
            return Variant(number);

        break;
    }

    Variant var;
    var.type = Type::UNKNOWN;

    return var;
}

void Variant::ToLua(lua_State * L) const
{
    switch (this->type)
    {
        case Type::SMALL_STRING:
            lua_pushlstring(L, data.smallString.string, data.smallString.length);
            break;
        case Type::STRING:
            lua_pushlstring(L, data.string, strlen(data.string));
            break;
        case Type::LOVE_OBJECT:
            Luax::PushObject(L, data.loveObject);
            break;
        case Type::BOOLEAN:
            lua_pushboolean(L, data.boolean);
            break;
        case Type::NUMBER:
            lua_pushnumber(L, data.number);
            break;
        case Type::NIL:
        default:
            lua_pushnil(L);
            break;
    }
}
