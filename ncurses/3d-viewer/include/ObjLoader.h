#pragma once

#include <string>

#include "Mesh.h"

class ObjLoader
{
public:
    static bool load(
        const std::string& filename,
        Mesh& mesh,
        std::string& error
    );
};
