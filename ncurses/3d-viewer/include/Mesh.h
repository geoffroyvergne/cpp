#pragma once

#include <vector>

#include "Vec3.h"

struct Triangle
{
    int v0;
    int v1;
    int v2;
};

struct Mesh
{
    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    Vec3 min;
    Vec3 max;

    void normalize();
};
