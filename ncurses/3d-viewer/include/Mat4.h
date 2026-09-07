#pragma once

#include "Vec3.h"

struct Mat4
{
    float m[4][4];

    Mat4();

    static Mat4 identity();

    static Mat4 rotationX(float angle);
    static Mat4 rotationY(float angle);
    static Mat4 rotationZ(float angle);

    Vec3 transformPoint(const Vec3& v) const;

    Mat4 operator*(const Mat4& other) const;
};
