#include "Vec3.h"

Vec3::Vec3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

Vec3::Vec3(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
{
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(
        x - other.x,
        y - other.y,
        z - other.z
    );
}

Vec3 Vec3::operator*(float value) const
{
    return Vec3(
        x * value,
        y * value,
        z * value
    );
}

Vec3 Vec3::operator/(float value) const
{
    return Vec3(
        x / value,
        y / value,
        z / value
    );
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

float Vec3::length() const
{
    return std::sqrt(
        x * x +
        y * y +
        z * z
    );
}

Vec3 Vec3::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vec3();

    return *this / len;
}

float Vec3::dot(const Vec3& a, const Vec3& b)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
