#pragma once

#include <vector>

#include "Mesh.h"

class Renderer
{
public:
    Renderer();

    void resize(int width, int height);

    void clear();

    void render(
        const Mesh& mesh,
        float rotationX,
        float rotationY,
        float rotationZ,
        float zoom
    );

    void present() const;

private:
    struct ProjectedVertex
    {
        float x;
        float y;
        float z;
        bool valid;
    };

    int width_;
    int height_;

    std::vector<char> framebuffer_;
    std::vector<float> depthbuffer_;

    void drawTriangle(
        const ProjectedVertex& a,
        const ProjectedVertex& b,
        const ProjectedVertex& c,
        char character
    );

    ProjectedVertex project(
        const Vec3& point,
        float aspect
    ) const;

    static char shadeFromIntensity(float intensity);
};
