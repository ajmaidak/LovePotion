#pragma once

namespace love
{
    class Window : public Module
    {
        public:
            virtual ~Window() {};

            virtual ModuleType GetModuleType() const { return M_WINDOW; }

            const char * GetName() const override { return "love.window"; }

            // Löve2D Functions

            void SetMode() { };

            int GetDisplayCount();

            std::vector<std::pair<int, int>> GetFullscreenModes();

            bool IsOpen();

            // End Löve2D Functions

        private:
            std::vector<std::pair<int, int>> displaySizes;
    };
}
