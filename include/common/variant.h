#pragma once

class Variant : public std::variant<std::monostate, bool, void *, Nil, float, std::string>
{
    public:
        static const int MAX_SMALL_STR_LENGTH = 15;

        enum Type
        {
            UNKNOWN = 0,
            BOOLEAN,
            LOVE_OBJECT,
            NIL,
            NUMBER,
            STRING
        };

        using std::variant<std::monostate, bool, void *, Nil, float, std::string>::variant;
        using std::variant<std::monostate, bool, void *, Nil, float, std::string>::operator=;

        std::string GetTypeString() const;
        Type GetType() const;

        static Variant FromLua(lua_State * L, int n);
        void ToLua(lua_State * L) const;
};
