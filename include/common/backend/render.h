/*
** render.h
** Renderer superclass
*/

class Render
{
    public:
        Render() = delete;

        static void Rectangle(const std::string & mode, float x, float y, float width, float height, const Color & color);

        static void Cicle(const std::string & mode, float x, float y, float radius, const Color & color);

        static void Polygon(const std::string & mode, const Color & color);

        static void Line(std::vector<float> points, const Color & color);

        static void Points(std::vector<std::vector<float>> points, const Color & color);

        static void Points(std::vector<float> points, const Color & color);

    private:
        static inline float m_lineWidth = 1.0f;
};
