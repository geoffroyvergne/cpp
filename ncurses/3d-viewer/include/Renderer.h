#pragma once

#include <vector>

#include "Mesh.h"
#include "Mat4.h"

class Renderer
{
public:
    enum class Mode
    {
        Solid,
        Wireframe,
        HalfBlock
    };

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

    void present();

    void setMode(Mode mode);

    Mode mode() const;

private:
    struct ProjectedVertex
    {
        float x;
        float y;
        float z;
    };

    int width_;
    int height_;

    Mode mode_;

    std::vector<unsigned char> framebuffer_;
    std::vector<char> halfFramebuffer_;
    std::vector<float> depthbuffer_;

    std::vector<ProjectedVertex> projected_;

    void renderSolid(
        const Mesh& mesh
    );

    void renderWireframe(
        const Mesh& mesh
    );

    void renderHalfBlock(
        const Mesh& mesh
    );

    ProjectedVertex project(
        const Vec3& point
    ) const;

    void drawTriangle(
        const ProjectedVertex& a,
        const ProjectedVertex& b,
        const ProjectedVertex& c,
        unsigned char intensity
    );

    void drawPixel(
        int x,
        int y,
        unsigned char intensity
    );

    void drawLine(
        int x0,
        int y0,
        int x1,
        int y1,
        char character
    );

    void drawTriangleHalfBlock(
        const ProjectedVertex& a,
        const ProjectedVertex& b,
        const ProjectedVertex& c,
        unsigned char intensity
    );

    unsigned char calculateLighting(
        const Vec3& normal
    ) const;

    static char intensityToAscii(
        unsigned char intensity
    );

    static const char* intensityToBlock(
        unsigned char intensity
    );
};