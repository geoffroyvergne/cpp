#include "Renderer.h"

#include "Mat4.h"

#include <ncurses.h>

#include <algorithm>
#include <cmath>

Renderer::Renderer()
    : width_(0),
      height_(0)
{
}

void Renderer::resize(int width, int height)
{
    width_ = std::max(1, width);
    height_ = std::max(1, height);

    framebuffer_.resize(
        static_cast<std::size_t>(width_) *
        static_cast<std::size_t>(height_)
    );

    depthbuffer_.resize(
        static_cast<std::size_t>(width_) *
        static_cast<std::size_t>(height_)
    );
}

void Renderer::clear()
{
    std::fill(
        framebuffer_.begin(),
        framebuffer_.end(),
        ' '
    );

    // We use a "larger = closer" depth convention.
    std::fill(
        depthbuffer_.begin(),
        depthbuffer_.end(),
        -1000000.0f
    );
}

void Renderer::render(
    const Mesh& mesh,
    float rotationX,
    float rotationY,
    float rotationZ,
    float zoom
)
{
    if (width_ <= 0 || height_ <= 0)
        return;

    /*
     * Terminal characters are normally approximately twice as high
     * as they are wide.
     *
     * Therefore one terminal character is not square in physical
     * space. The aspect correction compensates for this.
     */
    const float aspect =
        static_cast<float>(width_) /
        static_cast<float>(height_) *
        0.5f;

    /*
     * Rotation order:
     *
     *      Z * Y * X
     *
     * This gives intuitive independent X/Y/Z rotations.
     */
    const Mat4 rx = Mat4::rotationX(rotationX);
    const Mat4 ry = Mat4::rotationY(rotationY);
    const Mat4 rz = Mat4::rotationZ(rotationZ);

    const Mat4 rotation = rz * ry * rx;

    /*
     * Transform all vertices once.
     */
    std::vector<Vec3> transformed;
    transformed.reserve(mesh.vertices.size());

    for (const Vec3& vertex : mesh.vertices)
    {
        Vec3 p = rotation.transformPoint(vertex);

        /*
         * Zoom is applied after rotation so the model remains
         * centered around the origin.
         */
        p = p * zoom;

        transformed.push_back(p);
    }

    /*
     * Project vertices to terminal coordinates.
     */
    std::vector<ProjectedVertex> projected;
    projected.reserve(transformed.size());

    for (const Vec3& vertex : transformed)
    {
        projected.push_back(
            project(vertex, aspect)
        );
    }

    /*
     * Directional light.
     *
     * The light points toward the object.
     */
    const Vec3 light =
        Vec3(-0.5f, -0.8f, -1.0f).normalized();

    /*
     * Render every triangle.
     */
    for (const Triangle& triangle : mesh.triangles)
    {
        const Vec3& v0 =
            transformed[triangle.v0];

        const Vec3& v1 =
            transformed[triangle.v1];

        const Vec3& v2 =
            transformed[triangle.v2];

        /*
         * Compute face normal.
         */
        const Vec3 edge1 = v1 - v0;
        const Vec3 edge2 = v2 - v0;

        const Vec3 normal =
            Vec3::cross(edge1, edge2).normalized();

        /*
         * Lambert lighting.
         */
        float intensity =
            Vec3::dot(normal, light);

        /*
         * Keep the back side visible but darker.
         */
        intensity =
            std::max(0.0f, intensity);

        /*
         * Ambient light.
         *
         * This is deliberately stronger than before so the model
         * doesn't collapse into almost invisible dots.
         */
        intensity =
            0.25f +
            intensity * 0.75f;

        intensity =
            std::clamp(
                intensity,
                0.0f,
                1.0f
            );

        const char character =
            shadeFromIntensity(intensity);

        const ProjectedVertex& p0 =
            projected[triangle.v0];

        const ProjectedVertex& p1 =
            projected[triangle.v1];

        const ProjectedVertex& p2 =
            projected[triangle.v2];

        /*
         * Don't draw triangles for which a vertex is behind
         * the camera.
         *
         * A proper near-plane clipping stage can be added later.
         */
        if (!p0.valid ||
            !p1.valid ||
            !p2.valid)
        {
            continue;
        }

        drawTriangle(
            p0,
            p1,
            p2,
            character
        );
    }
}

void Renderer::present() const
{
    /*
     * IMPORTANT:
     *
     * Do NOT use std::cout here.
     *
     * The rest of the application uses ncurses, so writing directly
     * to stdout causes the terminal to flicker/blink when ncurses
     * subsequently calls refresh().
     */

    for (int y = 0; y < height_; ++y)
    {
        const std::size_t offset =
            static_cast<std::size_t>(y) *
            static_cast<std::size_t>(width_);

        /*
         * Write the complete framebuffer line through ncurses.
         */
        move(y, 0);

        for (int x = 0; x < width_; ++x)
        {
            addch(
                static_cast<unsigned char>(
                    framebuffer_[offset + x]
                )
            );
        }

        /*
         * Make sure characters left over from a previous frame
         * are erased if the terminal was resized.
         */
        clrtoeol();
    }
}

Renderer::ProjectedVertex Renderer::project(
    const Vec3& point,
    float aspect
) const
{
    ProjectedVertex result{};

    /*
     * Camera is located at z = -4 and looks toward +Z.
     *
     * The model is therefore translated forward by 4 units.
     */
    const float cameraZ =
        point.z + 4.0f;

    /*
     * Near clipping plane.
     */
    constexpr float nearPlane = 0.1f;

    if (cameraZ <= nearPlane)
    {
        result.valid = false;
        return result;
    }

    /*
     * Field of view.
     */
    constexpr float PI =
        3.14159265358979323846f;

    constexpr float FOV =
        70.0f;

    const float f =
        1.0f /
        std::tan(
            FOV *
            0.5f *
            PI /
            180.0f
        );

    /*
     * Perspective projection.
     */
    const float projectedX =
        (point.x * f) /
        (cameraZ * aspect);

    const float projectedY =
        (point.y * f) /
        cameraZ;

    /*
     * Convert normalized device coordinates [-1,+1]
     * into terminal coordinates.
     */
    result.x =
        (projectedX + 1.0f) *
        0.5f *
        static_cast<float>(width_ - 1);

    result.y =
        (1.0f - projectedY) *
        0.5f *
        static_cast<float>(height_ - 1);

    /*
     * Larger depth value means closer to the camera.
     */
    result.z =
        1.0f / cameraZ;

    result.valid = true;

    return result;
}

char Renderer::shadeFromIntensity(
    float intensity
)
{
    /*
     * From darkest to brightest.
     *
     * The previous palette was too limited, which made the cube
     * appear almost entirely as '.' characters.
     */
    static constexpr char shades[] =
        " .:-=+*#%@";

    constexpr int shadeCount =
        static_cast<int>(
            sizeof(shades) - 1
        );

    intensity =
        std::clamp(
            intensity,
            0.0f,
            1.0f
        );

    /*
     * Slight gamma correction.
     *
     * This gives considerably more useful contrast in a terminal.
     */
    intensity =
        std::pow(
            intensity,
            0.75f
        );

    int index =
        static_cast<int>(
            intensity *
            static_cast<float>(shadeCount - 1)
        );

    index =
        std::clamp(
            index,
            0,
            shadeCount - 1
        );

    return shades[index];
}

void Renderer::drawTriangle(
    const ProjectedVertex& a,
    const ProjectedVertex& b,
    const ProjectedVertex& c,
    char character
)
{
    /*
     * Bounding box of the projected triangle.
     */
    const float minX =
        std::min({
            a.x,
            b.x,
            c.x
        });

    const float maxX =
        std::max({
            a.x,
            b.x,
            c.x
        });

    const float minY =
        std::min({
            a.y,
            b.y,
            c.y
        });

    const float maxY =
        std::max({
            a.y,
            b.y,
            c.y
        });

    int x0 =
        static_cast<int>(
            std::floor(minX)
        );

    int x1 =
        static_cast<int>(
            std::ceil(maxX)
        );

    int y0 =
        static_cast<int>(
            std::floor(minY)
        );

    int y1 =
        static_cast<int>(
            std::ceil(maxY)
        );

    /*
     * Clip bounding box to framebuffer.
     */
    x0 =
        std::max(
            x0,
            0
        );

    x1 =
        std::min(
            x1,
            width_ - 1
        );

    y0 =
        std::max(
            y0,
            0
        );

    y1 =
        std::min(
            y1,
            height_ - 1
        );

    if (x0 > x1 ||
        y0 > y1)
    {
        return;
    }

    /*
     * Edge function.
     */
    const float area =
        (b.x - a.x) *
        (c.y - a.y)
        -
        (b.y - a.y) *
        (c.x - a.x);

    /*
     * Degenerate triangle.
     */
    if (std::abs(area) < 0.000001f)
        return;

    const float inverseArea =
        1.0f / area;

    for (int y = y0; y <= y1; ++y)
    {
        for (int x = x0; x <= x1; ++x)
        {
            /*
             * Pixel center.
             */
            const float px =
                static_cast<float>(x) +
                0.5f;

            const float py =
                static_cast<float>(y) +
                0.5f;

            /*
             * Barycentric coordinates.
             */
            const float w0 =
                (
                    (b.x - px) *
                    (c.y - py)
                    -
                    (b.y - py) *
                    (c.x - px)
                ) *
                inverseArea;

            const float w1 =
                (
                    (c.x - px) *
                    (a.y - py)
                    -
                    (c.y - py) *
                    (a.x - px)
                ) *
                inverseArea;

            const float w2 =
                1.0f -
                w0 -
                w1;

            /*
             * Point is inside triangle.
             *
             * Small tolerance avoids holes caused by floating-point
             * precision on triangle edges.
             */
            constexpr float epsilon =
                -0.0001f;

            if (w0 < epsilon ||
                w1 < epsilon ||
                w2 < epsilon)
            {
                continue;
            }

            /*
             * Perspective-correct-ish depth interpolation.
             *
             * For our relatively small terminal renderer this is
             * sufficient and much better than simply using the
             * triangle's average depth.
             */
            const float depth =
                w0 * a.z +
                w1 * b.z +
                w2 * c.z;

            const std::size_t index =
                static_cast<std::size_t>(y) *
                static_cast<std::size_t>(width_) +
                static_cast<std::size_t>(x);

            /*
             * Z-buffer test.
             */
            if (depth <= depthbuffer_[index])
                continue;

            depthbuffer_[index] = depth;
            framebuffer_[index] = character;
        }
    }
}
