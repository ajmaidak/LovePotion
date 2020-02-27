#pragma once

#include "common/backend/display.h"

namespace love
{
    class Image : public Object
    {
        public:
            static love::Type type;

            Image(const std::string & path);

            void Draw(float x, float y, float r, float scalarX, float scalarY);

            int GetWidth() { return width; }

            int GetHeight() { return height; }

            void SetFilter();

        private:
            int width;
            int height;

            Texture texture;

    };
}
