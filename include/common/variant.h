#pragma once

#include "objects/object.h"

class Variant : public std::variant<std::monostate, bool, Proxy, void *, Nil, float, std::string>
{
    public:
        enum Type
        {
            UNKNOWN = 0,
            BOOLEAN,
            LOVE_OBJECT,
            LUSERDATA,
            NIL,
            NUMBER,
            STRING
        };

        using std::variant<std::monostate, bool, Proxy, void *, Nil, float, std::string>::variant;
        using std::variant<std::monostate, bool, Proxy, void *, Nil, float, std::string>::operator=;

        Variant & operator= (const Variant & v);

        ~Variant();

        static Proxy * TryExtractProxy(lua_State * L, size_t index);

        std::string GetTypeString() const;
        Type GetType() const;

        static Variant FromLua(lua_State * L, int n);
        void ToLua(lua_State * L) const;
};
