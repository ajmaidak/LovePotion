#include "common/runtime.h"
#include "modules/mod_thread.h"

int LoveThread::GetChannel(lua_State * L)
{
    // const char * name = luaL_checkstring(L, 1);
    // int returnValue = 0;

    // if (channels.find(name) == channels.end()) //create one
    //     returnValue = channelNew(L);
    // else
    // {
    //     Channel * self = channels[name];

    //     if (!love_is_registered(L, self))
    //         returnValue = channelNew(L, self); //reuse the pointer, register it
    //     else
    //     {
    //         love_push_userdata(L, self);
    //         returnValue = 1;
    //     }
    // }

    // return returnValue;
    return 0;
}

void LoveThread::Exit()
{
    //for (auto thread : threads)
    //    thread->Collect();
}

int LoveThread::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        // { "getChannel", GetChannel },
        // { "newChannel", channelNew },
        // { "newThread",  threadNew  },
        { 0, 0 }
    };

    love_register_module(L, "love.thread", reg);

    return 1;
}
