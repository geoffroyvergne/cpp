#include "Mesh.h"

#include <algorithm>
#include <cmath>

void Mesh::normalize()
{
    if (vertices.empty())
        return;

    min = vertices[0];
    max = vertices[0];

    for (const Vec3& v : vertices)
    {
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        min.z = std::min(min.z, v.z);

        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
        max.z = std::max(max.z, v.z);
    }

    const Vec3 center(
        (min.x + max.x) * 0.5f,
        (min.y + max.y) * 0.5f,
        (min.z + max.z) * 0.5f
    );

    const float sizeX = max.x - min.x;
    const float sizeY = max.y - min.y;
    const float sizeZ = max.z - min.z;

    const float maxSize =
        std::max({
            sizeX,
            sizeY,
            sizeZ
        });

    if (maxSize <= 0.000001f)
        return;

    const float scale = 2.0f / maxSize;

    for (Vec3& v : vertices)
    {
        v -= center;
        v = v * scale;
    }

    min = Vec3(-1.0f, -1.0f, -1.0f);
    max = Vec3(1.0f, 1.0f, 1.0f);
}
