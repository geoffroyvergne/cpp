#include "Mat4.h"

#include <cmath>

Mat4::Mat4()
{
    for (auto& row : m)
    {
        for (float& value : row)
        {
            value = 0.0f;
        }
    }
}

Mat4 Mat4::identity()
{
    Mat4 result;

    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;

    return result;
}

Mat4 Mat4::rotationX(float angle)
{
    Mat4 result = identity();

    const float c = std::cos(angle);
    const float s = std::sin(angle);

    result.m[1][1] = c;
    result.m[1][2] = -s;
    result.m[2][1] = s;
    result.m[2][2] = c;

    return result;
}

Mat4 Mat4::rotationY(float angle)
{
    Mat4 result = identity();

    const float c = std::cos(angle);
    const float s = std::sin(angle);

    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;

    return result;
}

Mat4 Mat4::rotationZ(float angle)
{
    Mat4 result = identity();

    const float c = std::cos(angle);
    const float s = std::sin(angle);

    result.m[0][0] = c;
    result.m[0][1] = -s;
    result.m[1][0] = s;
    result.m[1][1] = c;

    return result;
}

Vec3 Mat4::transformPoint(const Vec3& v) const
{
    const float x =
        m[0][0] * v.x +
        m[0][1] * v.y +
        m[0][2] * v.z +
        m[0][3];

    const float y =
        m[1][0] * v.x +
        m[1][1] * v.y +
        m[1][2] * v.z +
        m[1][3];

    const float z =
        m[2][0] * v.x +
        m[2][1] * v.y +
        m[2][2] * v.z +
        m[2][3];

    const float w =
        m[3][0] * v.x +
        m[3][1] * v.y +
        m[3][2] * v.z +
        m[3][3];

    if (std::abs(w) > 0.000001f)
    {
        return Vec3(
            x / w,
            y / w,
            z / w
        );
    }

    return Vec3(x, y, z);
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            for (int k = 0; k < 4; ++k)
            {
                result.m[row][col] +=
                    m[row][k] * other.m[k][col];
            }
        }
    }

    return result;
}
