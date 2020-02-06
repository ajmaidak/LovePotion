#pragma once

// TODO: extend via std::variant<const std::string &, float, void *>
// this will allow use of stdlib variant that does the same stuff
// thanks @piepie

class Variant
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
            SMALL_STRING,
            STRING
        };

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

        Variant();
        Variant(bool boolean);
        Variant(float number);
        Variant(const char * string, size_t length);
        Variant(const std::string & string);
        Variant(void * lightuserdata);

        Variant(const Variant & v);
        Variant(Variant &&);
        ~Variant();

        Variant & operator = (const Variant & v);

        Type GetType() const { return type; }
        const Data & GetData() const { return data; }

        static Variant FromLua(lua_State * L, int n);
        void ToLua(lua_State * L) const;

    private:
        Type type;
        Data data;
};
