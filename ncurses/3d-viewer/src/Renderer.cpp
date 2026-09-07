#include "Renderer.h"

#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <limits>

namespace
{

constexpr const char* UTF8_FULL_BLOCK =
    "\xE2\x96\x88"; // █

constexpr const char* UTF8_UPPER_BLOCK =
    "\xE2\x96\x80"; // ▀

constexpr const char* UTF8_LOWER_BLOCK =
    "\xE2\x96\x84"; // ▄

/*
 * Terminal character aspect ratio.
 *
 * A normal terminal character is approximately
 * twice as high as it is wide.
 *
 * Therefore:
 *
 *   Solid / Wireframe : X * 2
 *   HalfBlock         : X * 1
 */
constexpr float SOLID_ASPECT = 2.0f;
constexpr float HALFBLOCK_ASPECT = 1.0f;

/*
 * Near clipping plane.
 *
 * Anything closer than this distance to the
 * camera is ignored.
 */
constexpr float NEAR_CLIP = 0.05f;

/*
 * Small numerical tolerance used by the
 * barycentric rasterizer.
 */
constexpr float RASTER_EPSILON = 0.00001f;

}

Renderer::Renderer()
    : width_(0),
      height_(0),
      mode_(Mode::Solid)
{
}

void Renderer::resize(
    int width,
    int height)
{
    width_ = std::max(1, width);
    height_ = std::max(1, height);

    framebuffer_.resize(
        static_cast<std::size_t>(
            width_ * height_
        )
    );

    halfFramebuffer_.resize(
        static_cast<std::size_t>(
            width_ * height_ * 2
        )
    );

    depthbuffer_.resize(
        static_cast<std::size_t>(
            width_ * height_ * 2
        )
    );

    projected_.clear();

    clear();
}

void Renderer::clear()
{
    std::fill(
        framebuffer_.begin(),
        framebuffer_.end(),
        0
    );

    std::fill(
        halfFramebuffer_.begin(),
        halfFramebuffer_.end(),
        0
    );

    std::fill(
        depthbuffer_.begin(),
        depthbuffer_.end(),
        std::numeric_limits<float>::infinity()
    );
}

void Renderer::setMode(
    Mode mode)
{
    mode_ = mode;
}

Renderer::Mode Renderer::mode() const
{
    return mode_;
}

Renderer::ProjectedVertex Renderer::project(
    const Vec3& point) const
{
    ProjectedVertex result{};

    /*
     * Distance from the camera to the origin.
     */
    constexpr float cameraDistance = 4.0f;

    const float z =
        point.z + cameraDistance;

    /*
     * Vertex is behind / too close to camera.
     */
    if (z <= NEAR_CLIP)
    {
        result.x = -10000.0f;
        result.y = -10000.0f;
        result.z = z;

        return result;
    }

    /*
     * Projection scale.
     *
     * Height is used as the reference dimension.
     */
    const float focalLength =
        static_cast<float>(height_) * 0.75f;

    /*
     * Compensate terminal character aspect ratio.
     */
    const float aspectX =
        mode_ == Mode::HalfBlock
            ? HALFBLOCK_ASPECT
            : SOLID_ASPECT;

    /*
     * Perspective projection.
     */
    result.x =
        static_cast<float>(width_) * 0.5f +
        point.x *
        focalLength *
        aspectX /
        z;

    result.y =
        static_cast<float>(height_) * 0.5f -
        point.y *
        focalLength /
        z;

    result.z = z;

    return result;
}

unsigned char Renderer::calculateLighting(
    const Vec3& normal) const
{
    const Vec3 lightDirection =
        Vec3(
            -0.5f,
            0.8f,
            1.0f
        ).normalized();

    const Vec3 n =
        normal.normalized();

    const float diffuse =
        std::max(
            0.0f,
            Vec3::dot(
                n,
                lightDirection
            )
        );

    constexpr float ambient = 0.12f;

    const float intensity =
        ambient +
        diffuse * 0.88f;

    const float clamped =
        std::clamp(
            intensity,
            0.0f,
            1.0f
        );

    return static_cast<unsigned char>(
        clamped * 255.0f
    );
}

char Renderer::intensityToAscii(
    unsigned char intensity)
{
    static constexpr const char* shades =
        " .:-=+*#%@";

    constexpr int shadeCount = 10;

    const int index =
        static_cast<int>(intensity) *
        (shadeCount - 1) /
        255;

    return shades[index];
}

const char* Renderer::intensityToBlock(
    unsigned char intensity)
{
    if (intensity < 32)
        return " ";

    if (intensity < 75)
        return "\xE2\x96\x91"; // ░

    if (intensity < 125)
        return "\xE2\x96\x92"; // ▒

    if (intensity < 175)
        return "\xE2\x96\x93"; // ▓

    return UTF8_FULL_BLOCK;
}

void Renderer::drawPixel(
    int x,
    int y,
    unsigned char intensity)
{
    if (x < 0 ||
        x >= width_ ||
        y < 0 ||
        y >= height_)
    {
        return;
    }

    const std::size_t index =
        static_cast<std::size_t>(
            y * width_ + x
        );

    framebuffer_[index] =
        std::max(
            framebuffer_[index],
            intensity
        );
}

void Renderer::drawLine(
    int x0,
    int y0,
    int x1,
    int y1,
    char character)
{
    (void)character;

    const int dx =
        std::abs(x1 - x0);

    const int sx =
        x0 < x1 ? 1 : -1;

    const int dy =
        -std::abs(y1 - y0);

    const int sy =
        y0 < y1 ? 1 : -1;

    int error =
        dx + dy;

    while (true)
    {
        drawPixel(
            x0,
            y0,
            255
        );

        if (x0 == x1 &&
            y0 == y1)
        {
            break;
        }

        const int e2 =
            2 * error;

        if (e2 >= dy)
        {
            error += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

void Renderer::drawTriangle(
    const ProjectedVertex& a,
    const ProjectedVertex& b,
    const ProjectedVertex& c,
    unsigned char intensity)
{
    /*
     * Do not rasterize triangles that cross the
     * near plane.
     *
     * Proper polygon clipping could be implemented
     * later, but skipping such triangles avoids
     * the huge projection artifacts that otherwise
     * appear when zooming very close to the object.
     */
    if (a.z <= NEAR_CLIP ||
        b.z <= NEAR_CLIP ||
        c.z <= NEAR_CLIP)
    {
        return;
    }

    const float minXF =
        std::min({
            a.x,
            b.x,
            c.x
        });

    const float maxXF =
        std::max({
            a.x,
            b.x,
            c.x
        });

    const float minYF =
        std::min({
            a.y,
            b.y,
            c.y
        });

    const float maxYF =
        std::max({
            a.y,
            b.y,
            c.y
        });

    /*
     * Completely outside the screen.
     */
    if (maxXF < 0.0f ||
        minXF >= static_cast<float>(width_) ||
        maxYF < 0.0f ||
        minYF >= static_cast<float>(height_))
    {
        return;
    }

    const int minX =
        std::max(
            0,
            static_cast<int>(
                std::floor(minXF)
            )
        );

    const int maxX =
        std::min(
            width_ - 1,
            static_cast<int>(
                std::ceil(maxXF)
            )
        );

    const int minY =
        std::max(
            0,
            static_cast<int>(
                std::floor(minYF)
            )
        );

    const int maxY =
        std::min(
            height_ - 1,
            static_cast<int>(
                std::ceil(maxYF)
            )
        );

    /*
     * Triangle signed area.
     */
    const float area =
        (b.x - a.x) *
        (c.y - a.y) -
        (b.y - a.y) *
        (c.x - a.x);

    if (std::abs(area) < RASTER_EPSILON)
        return;

    /*
     * Inverse area avoids performing the division
     * three times for every pixel.
     */
    const float inverseArea =
        1.0f / area;

    /*
     * Perspective-correct depth uses 1/z.
     *
     * This is important because simply interpolating
     * z linearly in screen space can produce incorrect
     * depth ordering between overlapping triangles.
     */
    const float invZa =
        1.0f / a.z;

    const float invZb =
        1.0f / b.z;

    const float invZc =
        1.0f / c.z;

    for (int y = minY;
         y <= maxY;
         ++y)
    {
        for (int x = minX;
             x <= maxX;
             ++x)
        {
            const float px =
                static_cast<float>(x) + 0.5f;

            const float py =
                static_cast<float>(y) + 0.5f;

            const float w0 =
                (
                    (b.x - a.x) *
                    (py - a.y) -
                    (b.y - a.y) *
                    (px - a.x)
                ) *
                inverseArea;

            const float w1 =
                (
                    (c.x - b.x) *
                    (py - b.y) -
                    (c.y - b.y) *
                    (px - b.x)
                ) *
                inverseArea;

            const float w2 =
                (
                    (a.x - c.x) *
                    (py - c.y) -
                    (a.y - c.y) *
                    (px - c.x)
                ) *
                inverseArea;

            /*
             * Small epsilon prevents tiny gaps caused
             * by floating-point precision along edges.
             */
            if (w0 < -RASTER_EPSILON ||
                w1 < -RASTER_EPSILON ||
                w2 < -RASTER_EPSILON)
            {
                continue;
            }

            /*
             * Perspective-correct depth.
             */
            const float inverseZ =
                w0 * invZa +
                w1 * invZb +
                w2 * invZc;

            if (inverseZ <= 0.0f)
                continue;

            const float depth =
                1.0f / inverseZ;

            const std::size_t index =
                static_cast<std::size_t>(
                    y * width_ + x
                );

            /*
             * Smaller Z = closer to camera.
             *
             * The small epsilon avoids unstable
             * overwrites when two coplanar triangles
             * have virtually identical depth.
             */
            if (depth <
                depthbuffer_[index] - 0.000001f)
            {
                depthbuffer_[index] =
                    depth;

                framebuffer_[index] =
                    intensity;
            }
        }
    }
}

void Renderer::drawTriangleHalfBlock(
    const ProjectedVertex& a,
    const ProjectedVertex& b,
    const ProjectedVertex& c,
    unsigned char intensity)
{
    if (a.z <= NEAR_CLIP ||
        b.z <= NEAR_CLIP ||
        c.z <= NEAR_CLIP)
    {
        return;
    }

    const int halfHeight =
        height_ * 2;

    /*
     * HalfBlock coordinates use two vertical
     * pixels per terminal row.
     */
    const float ay =
        a.y * 2.0f;

    const float by =
        b.y * 2.0f;

    const float cy =
        c.y * 2.0f;

    const float minXF =
        std::min({
            a.x,
            b.x,
            c.x
        });

    const float maxXF =
        std::max({
            a.x,
            b.x,
            c.x
        });

    const float minYF =
        std::min({
            ay,
            by,
            cy
        });

    const float maxYF =
        std::max({
            ay,
            by,
            cy
        });

    /*
     * Completely outside the screen.
     */
    if (maxXF < 0.0f ||
        minXF >= static_cast<float>(width_) ||
        maxYF < 0.0f ||
        minYF >= static_cast<float>(halfHeight))
    {
        return;
    }

    const int minX =
        std::max(
            0,
            static_cast<int>(
                std::floor(minXF)
            )
        );

    const int maxX =
        std::min(
            width_ - 1,
            static_cast<int>(
                std::ceil(maxXF)
            )
        );

    const int minY =
        std::max(
            0,
            static_cast<int>(
                std::floor(minYF)
            )
        );

    const int maxY =
        std::min(
            halfHeight - 1,
            static_cast<int>(
                std::ceil(maxYF)
            )
        );

    const float area =
        (b.x - a.x) *
        (cy - ay) -
        (by - ay) *
        (c.x - a.x);

    if (std::abs(area) < RASTER_EPSILON)
        return;

    const float inverseArea =
        1.0f / area;

    /*
     * Perspective-correct depth.
     */
    const float invZa =
        1.0f / a.z;

    const float invZb =
        1.0f / b.z;

    const float invZc =
        1.0f / c.z;

    for (int y = minY;
         y <= maxY;
         ++y)
    {
        for (int x = minX;
             x <= maxX;
             ++x)
        {
            const float px =
                static_cast<float>(x) + 0.5f;

            const float py =
                static_cast<float>(y) + 0.5f;

            const float w0 =
                (
                    (b.x - a.x) *
                    (py - ay) -
                    (by - ay) *
                    (px - a.x)
                ) *
                inverseArea;

            const float w1 =
                (
                    (c.x - b.x) *
                    (py - by) -
                    (cy - by) *
                    (px - b.x)
                ) *
                inverseArea;

            const float w2 =
                (
                    (a.x - c.x) *
                    (py - cy) -
                    (ay - cy) *
                    (px - c.x)
                ) *
                inverseArea;

            if (w0 < -RASTER_EPSILON ||
                w1 < -RASTER_EPSILON ||
                w2 < -RASTER_EPSILON)
            {
                continue;
            }

            const float inverseZ =
                w0 * invZa +
                w1 * invZb +
                w2 * invZc;

            if (inverseZ <= 0.0f)
                continue;

            const float depth =
                1.0f / inverseZ;

            const std::size_t index =
                static_cast<std::size_t>(
                    y * width_ + x
                );

            if (depth <
                depthbuffer_[index] - 0.000001f)
            {
                depthbuffer_[index] =
                    depth;

                halfFramebuffer_[index] =
                    static_cast<char>(
                        intensity
                    );
            }
        }
    }
}

void Renderer::renderSolid(
    const Mesh& mesh)
{
    /*
     * Clear framebuffer and z-buffer specifically
     * for Solid rendering.
     */
    std::fill(
        framebuffer_.begin(),
        framebuffer_.end(),
        0
    );

    std::fill(
        depthbuffer_.begin(),
        depthbuffer_.end(),
        std::numeric_limits<float>::infinity()
    );

    for (const Triangle& triangle :
         mesh.triangles)
    {
        const Vec3& v0 =
            mesh.vertices[triangle.v0];

        const Vec3& v1 =
            mesh.vertices[triangle.v1];

        const Vec3& v2 =
            mesh.vertices[triangle.v2];

        const Vec3 edge1 =
            v1 - v0;

        const Vec3 edge2 =
            v2 - v0;

        const Vec3 normal =
            Vec3::cross(
                edge1,
                edge2
            ).normalized();

        const unsigned char intensity =
            calculateLighting(normal);

        drawTriangle(
            projected_[triangle.v0],
            projected_[triangle.v1],
            projected_[triangle.v2],
            intensity
        );
    }
}

void Renderer::renderWireframe(
    const Mesh& mesh)
{
    /*
     * Wireframe does not use the z-buffer.
     * This is intentional: it displays the complete
     * topology of the mesh.
     */
    for (const Triangle& triangle :
         mesh.triangles)
    {
        const ProjectedVertex& a =
            projected_[triangle.v0];

        const ProjectedVertex& b =
            projected_[triangle.v1];

        const ProjectedVertex& c =
            projected_[triangle.v2];

        /*
         * Don't draw edges belonging to vertices
         * behind the camera.
         */
        if (a.z <= NEAR_CLIP ||
            b.z <= NEAR_CLIP ||
            c.z <= NEAR_CLIP)
        {
            continue;
        }

        drawLine(
            static_cast<int>(a.x),
            static_cast<int>(a.y),
            static_cast<int>(b.x),
            static_cast<int>(b.y),
            '#'
        );

        drawLine(
            static_cast<int>(b.x),
            static_cast<int>(b.y),
            static_cast<int>(c.x),
            static_cast<int>(c.y),
            '#'
        );

        drawLine(
            static_cast<int>(c.x),
            static_cast<int>(c.y),
            static_cast<int>(a.x),
            static_cast<int>(a.y),
            '#'
        );
    }
}

void Renderer::renderHalfBlock(
    const Mesh& mesh)
{
    /*
     * Clear HalfBlock framebuffer and z-buffer.
     */
    std::fill(
        halfFramebuffer_.begin(),
        halfFramebuffer_.end(),
        0
    );

    std::fill(
        depthbuffer_.begin(),
        depthbuffer_.end(),
        std::numeric_limits<float>::infinity()
    );

    for (const Triangle& triangle :
         mesh.triangles)
    {
        const Vec3& v0 =
            mesh.vertices[triangle.v0];

        const Vec3& v1 =
            mesh.vertices[triangle.v1];

        const Vec3& v2 =
            mesh.vertices[triangle.v2];

        const Vec3 edge1 =
            v1 - v0;

        const Vec3 edge2 =
            v2 - v0;

        const Vec3 normal =
            Vec3::cross(
                edge1,
                edge2
            ).normalized();

        const unsigned char intensity =
            calculateLighting(normal);

        drawTriangleHalfBlock(
            projected_[triangle.v0],
            projected_[triangle.v1],
            projected_[triangle.v2],
            intensity
        );
    }
}

void Renderer::render(
    const Mesh& mesh,
    float rotationX,
    float rotationY,
    float rotationZ,
    float zoom)
{
    if (width_ <= 0 ||
        height_ <= 0)
    {
        return;
    }

    /*
     * Rotation order:
     *
     * X -> Y -> Z
     */
    const Mat4 rotation =
        Mat4::rotationZ(rotationZ) *
        Mat4::rotationY(rotationY) *
        Mat4::rotationX(rotationX);

    projected_.resize(
        mesh.vertices.size()
    );

    for (std::size_t i = 0;
         i < mesh.vertices.size();
         ++i)
    {
        Vec3 transformed =
            rotation.transformPoint(
                mesh.vertices[i]
            );

        /*
         * Zoom.
         */
        transformed.x *= zoom;
        transformed.y *= zoom;
        transformed.z *= zoom;

        /*
         * Project.
         */
        projected_[i] =
            project(transformed);
    }

    switch (mode_)
    {
        case Mode::Solid:
            renderSolid(mesh);
            break;

        case Mode::Wireframe:
            renderWireframe(mesh);
            break;

        case Mode::HalfBlock:
            renderHalfBlock(mesh);
            break;
    }
}

void Renderer::present()
{
    if (mode_ == Mode::HalfBlock)
    {
        for (int y = 0;
             y < height_;
             ++y)
        {
            move(y, 0);

            for (int x = 0;
                 x < width_;
                 ++x)
            {
                const std::size_t topIndex =
                    static_cast<std::size_t>(
                        (y * 2) * width_ + x
                    );

                const std::size_t bottomIndex =
                    static_cast<std::size_t>(
                        (y * 2 + 1) * width_ + x
                    );

                const unsigned char top =
                    static_cast<unsigned char>(
                        halfFramebuffer_[topIndex]
                    );

                const unsigned char bottom =
                    static_cast<unsigned char>(
                        halfFramebuffer_[bottomIndex]
                    );

                if (top == 0 &&
                    bottom == 0)
                {
                    addch(' ');
                }
                else if (top > 0 &&
                         bottom > 0)
                {
                    const unsigned char average =
                        static_cast<unsigned char>(
                            (
                                static_cast<int>(top) +
                                static_cast<int>(bottom)
                            ) / 2
                        );

                    addstr(
                        intensityToBlock(
                            average
                        )
                    );
                }
                else if (top > 0)
                {
                    addstr(
                        UTF8_UPPER_BLOCK
                    );
                }
                else
                {
                    addstr(
                        UTF8_LOWER_BLOCK
                    );
                }
            }
        }

        return;
    }

    /*
     * Solid / Wireframe.
     */
    for (int y = 0;
         y < height_;
         ++y)
    {
        move(y, 0);

        for (int x = 0;
             x < width_;
             ++x)
        {
            const std::size_t index =
                static_cast<std::size_t>(
                    y * width_ + x
                );

            const unsigned char intensity =
                framebuffer_[index];

            if (intensity == 0)
            {
                addch(' ');
                continue;
            }

            if (mode_ == Mode::Wireframe)
            {
                addch('#');
            }
            else
            {
                addstr(
                    intensityToBlock(
                        intensity
                    )
                );
            }
        }
    }
}