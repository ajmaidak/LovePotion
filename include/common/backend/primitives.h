/*
** render.h
** Renderer superclass
*/

#pragma once

namespace Primitives
{
    void Rectangle(const std::string & mode, float x, float y, float width, float height, float rx, float ry, const Color & color);

    void Circle(const std::string & mode, float x, float y, float radius, const Color & color);

    void Polygon(const std::string & mode, std::vector<love::Graphics::Point> points, const Color & color);

    void Line(float x1, float y1, float x2, float y2, const Color & color);

    void Points(std::vector<std::vector<float>> points, const Color & color);

    void Points(std::vector<float> points, const Color & color);

    void Scissor(bool enabled, float x, float y, float width, float height);

    void Stencil();
}
