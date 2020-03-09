#include "common/runtime.h"
#include "modules/audio/audio.h"

using namespace love;

Audio::Audio()
{}

Audio::~Audio()
{}

Source * Audio::NewSource(Decoder * decoder)
{
    return new Source(decoder);
}

void Audio::Stop(Source * source)
{
    source->Stop();
}

void Audio::Stop()
{

}
