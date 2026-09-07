#include "ObjLoader.h"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace
{

int parseVertexIndex(
    const std::string& token,
    int vertexCount)
{
    std::string indexString = token;

    const std::size_t slash = indexString.find('/');

    if (slash != std::string::npos)
        indexString = indexString.substr(0, slash);

    if (indexString.empty())
        return -1;

    int index = std::stoi(indexString);

    // OBJ indices start at 1.
    if (index > 0)
        return index - 1;

    // Negative indices are relative to the end.
    if (index < 0)
        return vertexCount + index;

    return -1;
}

}

bool ObjLoader::load(
    const std::string& filename,
    Mesh& mesh,
    std::string& error)
{
    std::ifstream file(filename);

    if (!file)
    {
        error = "Cannot open OBJ file: " + filename;
        return false;
    }

    mesh.vertices.clear();
    mesh.triangles.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        if (line[0] == '#')
            continue;

        std::istringstream stream(line);

        std::string type;
        stream >> type;

        if (type == "v")
        {
            float x;
            float y;
            float z;

            if (!(stream >> x >> y >> z))
            {
                error = "Invalid vertex in OBJ file.";
                return false;
            }

            mesh.vertices.emplace_back(x, y, z);
        }
        else if (type == "f")
        {
            std::vector<int> indices;

            std::string token;

            while (stream >> token)
            {
                const int index =
                    parseVertexIndex(
                        token,
                        static_cast<int>(mesh.vertices.size())
                    );

                if (index < 0 ||
                    index >= static_cast<int>(mesh.vertices.size()))
                {
                    error = "Invalid face index in OBJ file.";
                    return false;
                }

                indices.push_back(index);
            }

            if (indices.size() < 3)
                continue;

            // Fan triangulation:
            //
            // 0,1,2
            // 0,2,3
            // 0,3,4
            // ...

            for (std::size_t i = 1; i + 1 < indices.size(); ++i)
            {
                mesh.triangles.push_back({
                    indices[0],
                    indices[i],
                    indices[i + 1]
                });
            }
        }
    }

    if (mesh.vertices.empty())
    {
        error = "OBJ file contains no vertices.";
        return false;
    }

    if (mesh.triangles.empty())
    {
        error = "OBJ file contains no faces.";
        return false;
    }

    mesh.normalize();

    return true;
}
