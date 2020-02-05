#pragma once

enum Type
{
    UNKNOWN = 0,
    BOOLEAN,
    LOVE_OBJECT,
    NIL,
    NUMBER,
    SMALL_STRING,
    STRING
};

#define MAX_SMALL_STR_LENGTH 15

class Variant
{
    public:
        Variant();
        Variant(const char * string, size_t length);
        Variant(const std::string & string);
        Variant(void * userdata);
        Variant(bool boolean);
        Variant(float number);

        Variant(Variant &&);
        Variant(const Variant & v);
        Variant & operator = (const Variant & v);

        ~Variant();

        static Variant FromLua(lua_State * L, int n);
        void ToLua(lua_State * L) const;

    private:
        union Data
        {
            bool boolean;
            float number;

            char * string;

            struct
            {
                char string[MAX_SMALL_STR_LENGTH];
                u8 length;
            } smallString;

            void * loveObject;
        };

        Type type;
        Data data;
};
