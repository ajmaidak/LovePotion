#pragma once

#include "common/exception.h"
#include "common/mmath.h"

namespace love
{
    class Font : public Object
    {
        public:
            static love::Type type;

            static constexpr float DEFAULT_SIZE = 22.5f;

            Font(const std::string & path, float size = DEFAULT_SIZE);
            Font(float size = DEFAULT_SIZE);
            ~Font();

            void Print(const char * string, const DrawArgs & args, float * limit, const Color & color);

            float GetWidth(const char * text);
            float GetHeight();

            float GetSize();

        private:
            FontHandle font;
            TextBuffer buffer;
            float size;
            TextHandle text;

            TextureHandle texture;

            FontHandle LoadFromPath(const std::string & path);
            float GetScale() { return this->size / 30.0f; }
    };
}
