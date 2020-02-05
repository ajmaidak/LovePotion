#include "common/runtime.h"

Message::Message(const std::string & name, const std::vector<Variant> & args) : name(name), args(args)
{

}

int Message::ToLua(lua_State * L)
{
    lua_pushstring(L, this->name.c_str());

    for (const Variant & v : this->args)
        v.ToLua(L);

    return (int)this->args.size() + 1;
}
