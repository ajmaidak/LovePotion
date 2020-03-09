#include "common/runtime.h"
#include "modules/audio/wrap_audio.h"

using namespace love;

#define instance() (Module::GetInstance<Audio>(Module::M_AUDIO))

int Wrap_Audio::NewSource(lua_State * L)
{
    Source::Type type = Source::TYPE_STREAM;

    if (!Luax::IsType(L, 1, SoundData::type) && !Luax::IsType(L, 1, Decoder::type))
    {
        const char * typeString = luaL_checkstring(L, 2);

        // TO DO: check type

        if (type == Source::TYPE_QUEUE)
            return luaL_error(L, "Cannot create queueable sources using newSource. Use newQueueableSource instead.");
    }

    if (lua_isstring(L, 1) || Luax::IsType(L, 1, File::type) || Luax::IsType(L, 1, FileData::type))
        Luax::ConvertObject(L, 1, "sound", "newDecoder");

    Source * source = nullptr;

    Luax::CatchException(L, [&]() {
        if (Luax::IsType(L, 1, Decoder::type))
            source = instance()->NewSource(Luax::ToType<Decoder>(L, 1));
    });

    if (source != nullptr)
    {
        Luax::PushType(L, source);
        source->Release();

        return 1;
    }
    else
        return Luax::TypeErrror(L, 1, "Decoder or SoundData");
}

int Wrap_Audio::Stop(lua_State * L)
{
    if (lua_isnone(L, 1))
        instance()->Stop();
    else
    {
        // Source * source = Wrap_Source::CheckSource(L, 1);
        // source->Stop()
    }

    return 0;
}

int Wrap_Audio::Register(lua_State * L)
{
    Result res = ndspInit();

    if (res != 0)
        luaL_error(L, "Failed to initialize audio");

    luaL_Reg reg[] =
    {
        { "newSource", NewSource },
        { "stop",      Stop      },
        { 0,           0         }
    };

    lua_CFunction types[] =
    {
        Wrap_Source::Register,
        0
    };

    Audio * instance = instance();

    if (instance == nullptr)
        Luax::CatchException(L, [&]() { instance = new Audio(); });
    else
        instance->Retain();

    WrappedModule module;

    module.instance = instance;
    module.name = "audio";
    module.type = &Module::type;
    module.functions = reg;
    module.types = types;

    return Luax::RegisterModule(L, module);
}
