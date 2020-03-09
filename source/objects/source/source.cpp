#include "common/runtime.h"
#include "objects/source/source.h"

using namespace love;

love::Type Source::type("Source", &Object::type);

Source::Source(SoundData * sound) : sourceType(Source::TYPE_STATIC),
                                    sampleRate(sound->GetSampleRate()),
                                    channels(sound->GetChannelCount()),
                                    bitDepth(sound->GetBitDepth())

{

}

Source::Source(Decoder * decoder) : sourceType(Source::TYPE_STREAM),
                                    sampleRate(decoder->GetSampleRate()),
                                    channels(decoder->GetChannelCount()),
                                    bitDepth(decoder->GetBitDepth()),
                                    decoder(decoder),
                                    buffers(DEFAULT_BUFFERS)
{
    ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
    ndspChnSetRate(0, this->sampleRate);
    ndspChnSetInterp(0, NDSP_INTERP_POLYPHASE);


    u32 * buffer = (u32 *)linearAlloc(decoder->GetSize());
    this->waveBuffer.data_vaddr = &buffer;

    int decoded = std::max(decoder->Decode(), 0);
    memcpy(buffer, (u32 *)decoder->GetBuffer(), decoded);

        // /* sample count, divide by 2 because S T E R E O */
    this->waveBuffer.nsamples = decoded / 2;

    DSP_FlushDataCache(buffer, decoded);
    ndspChnWaveBufAdd(0, &this->waveBuffer);
}

int Source::StreamAtomic(void * buffer, Decoder * decoder)
{


    // if (decoded > 0)
    //     memcpy(buffer, decoder->GetBuffer(), decoded);

    // return decoded;
}

Source::Source(const Source & other)
{}

Source::~Source()
{
    this->Stop();
}

void Source::Stop()
{}

Source * Source::Clone()
{
    return new Source(*this);
}
