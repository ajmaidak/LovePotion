#pragma once

#include "objects/decoder/decoder.h"
#include "objects/sounddata/sounddata.h"

namespace love
{
    class Source : public Object
    {
        public:
            static love::Type type;

            enum Type
            {
                TYPE_STATIC,
                TYPE_STREAM,
                TYPE_QUEUE,
                TYPE_MAX_ENUM
            };

            enum Unit
            {
                UNIT_SECONDS,
                UNIT_SAMPLES,
                UNIT_MAX_ENUM
            };

            Source(SoundData * sound);
            Source(Decoder * decoder);
            Source(const Source & other);

            ~Source();

            Source * Clone();

            bool Play();

            void Stop();

            void Pause();

            bool IsPlaying() const;

            bool IsFinished() const;

            void SetVolume(float volume);

            float GetVolume() const;

            Type GetType() const;

        protected:
            Type sourceType;

        private:
            void Reset();

            int StreamAtomic(void * buffer, Decoder * decoder);

            bool valid = false;

            const static int DEFAULT_BUFFERS = 8;
            const static int MAX_BUFFERS = 64;

            float volume = 1.0f;
            bool looping = false;
            float minVolume = 0.0f;
            float maxVolume = 1.0f;

            int offsetSamples = 0;

            int sampleRate = 0;
            int channels = 0;
            int bitDepth = 0;

            StrongReference<Decoder> decoder;

            int buffers = 0;
            ndspWaveBuf waveBuffer;
    };
}
