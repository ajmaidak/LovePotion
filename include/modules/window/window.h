#pragma once

namespace love
{
    class Window : public Module
    {
        public:
            Window();
            ~Window();

            ModuleType GetModuleType() const { return M_WINDOW; }

            const char * GetName() const override { return "love.window"; }

            Renderer * GetRenderer();

            // Löve2D Functions

            int GetDisplayCount();

            std::vector<std::pair<int, int>> & GetFullscreenModes();

            bool IsOpen();

            void SetMode() { };

            void SetScreen(size_t screen);

            void Clear(Color * color);

            void Present();

            // End Löve2D Functions

            int GetDisplay() {
                return this->currentDisplay;
            };

        private:
            std::vector<std::pair<int, int>> displaySizes;
            std::vector<Renderer *> targets;
            Frame * window;
            bool open;

            int currentDisplay;
    };
}
