/*
** modules/graphics.h
** @brief : handles graphical drawing
*/

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
                DRAW_LINE,
                DRAW_FILL
            };

            struct DisplayState
            {
                Color foreground = { 1, 1, 1, 1 };
                Color background = { 0, 0, 0, 0 };

                float lineWidth = 2.0f;
                float pointSize = 2.0f;

                StrongReference<Font> font;

                Rect scissor;
            };

            struct Point
            {
                float x;
                float y;
            };

            static constexpr float MIN_DEPTH = 1.0f/16384.0f;
            static inline float CURRENT_DEPTH = 0;

            Graphics();
            ~Graphics();

            ModuleType GetModuleType() const { return M_GRAPHICS; }

            const char * GetName() const override { return "love.graphics"; }

            void Clear(float r, float g, float b);

            Color GetColor();

            void SetColor(const Color & color);

            Color GetBackgroundColor();

            void SetBackgroundColor(const Color & color);

            float GetLineWidth();

            void SetLineWidth(float width);

            void SetScissor(float x, float y, float width, float height);

            Rect GetScissor();

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


            void Present();

            void AdjustColor(const Color & in, Color * out);

            std::vector<DisplayState> states;

            static inline bool GetConstant(const std::string & in, DrawMode & out) {
                if (m_modes.find(in) != m_modes.end())
                {
                    out = m_modes[in];
                    return true;
                }

                return false;
            }

        private:
            void RestoreState(const DisplayState & state);
            void CheckSetDefaultFont();

            StrongReference<Font> defaultFont;

            static inline std::map<std::string, Graphics::DrawMode> m_modes =
            {
                { "line", DrawMode::DRAW_LINE },
                { "fill", DrawMode::DRAW_FILL }
            };
    };
}
