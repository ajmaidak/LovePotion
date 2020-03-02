/*
** modules/graphics.h
** @brief : handles graphical drawing
*/

#include "common/backend/render.h"

#include "objects/image/wrap_image.h"
#include "objects/image/image.h"

#include "objects/font/wrap_font.h"
#include "objects/font/font.h"

namespace love
{
    class Graphics : public Module
    {
        public:
            enum DrawMode
            {
                LINE,
                FILL
            };

            struct DisplayState
            {
                Color foreground = { 1, 1, 1, 1 };
                Color background = { 0, 0, 0, 0 };

                float lineWidth = 1.0f;
                float pointSize = 1.0f;

                bool scissor = false;
                StrongReference<Font> font;
            };

            Graphics();
            ~Graphics();

            ModuleType GetModuleType() const { return M_GRAPHICS; }

            const char * GetName() const override { return "love.graphics"; }

            void Clear(float r, float g, float b);

            Color GetColor();

            void SetColor(const Color & color);

            Color GetBackgroundColor();

            /* Objects */

            Image * NewImage(const std::string & path);

            Font * NewFont(const std::string & path, float size = Font::DEFAULT_SIZE);

            Font * NewFont(float size = Font::DEFAULT_SIZE);

            void SetFont(Font * font);

            Font * GetFont();

            void Print(const char * text, float x, float y);
            void Print(const char * string, Font * font, float x, float y);

            /* End Objects */

            void Reset();

            void SetBackgroundColor(const Color & color);

            void Present();

            void AdjustColor(const Color & in, Color * out);

            std::vector<DisplayState> states;

        private:
            void RestoreState(const DisplayState & state);
            void CheckSetDefaultFont();

            StrongReference<Font> defaultFont;

            static inline std::map<std::string, Graphics::DrawMode> m_modes =
            {
                { "line", DrawMode::LINE },
                { "fill", DrawMode::FILL }
            };

            static inline bool GetConstant(const std::string & in, DrawMode & out) {
                if (m_modes.find(in) != m_modes.end())
                {
                    out = m_modes[in];
                    return true;
                }

                return false;
            }
    };
}
