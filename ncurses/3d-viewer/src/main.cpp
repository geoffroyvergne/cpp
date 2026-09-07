#include <iostream>
#include <string>

#include "ObjLoader.h"
#include "Viewer.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <model.obj>"
            << std::endl;

        return 1;
    }

    Mesh mesh;

    std::string error;

    if (!ObjLoader::load(
            argv[1],
            mesh,
            error))
    {
        std::cerr
            << "Error: "
            << error
            << std::endl;

        return 1;
    }

    std::cout
        << "Loaded "
        << mesh.vertices.size()
        << " vertices and "
        << mesh.triangles.size()
        << " triangles."
        << std::endl;

    Viewer viewer(mesh);

    viewer.run();

    return 0;
}
