/*
** modules/graphics.h
** @brief : handles graphical drawing
*/

#include "common/backend/render.h"

#include "objects/image/wrap_image.h"
#include "objects/image/image.h"

class Graphics : public Module
{
    public:
        enum DrawMode
        {
            LINE,
            FILL
        };

        Graphics();
        virtual ~Graphics() {}

        virtual ModuleType GetModuleType() const { return M_GRAPHICS; }

        const char * GetName() const override { return "love.graphics"; }

        void Clear(float r, float g, float b);

        Color GetColor();

        void SetColor(const Color & color);

        Color GetBackgroundColor();

        void SetBackgroundColor(const Color & color);

        void Present();

        static void AdjustColor(const Color & in, Color * out);

    private:
        static inline float m_depth = 0.0f;
        static inline float m_lineWidth = 1.0f;

        Color backgroundColor;
        Color foregroundColor;

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
