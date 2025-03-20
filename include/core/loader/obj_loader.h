#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <map>

#include <core/resources/mesh.h>

namespace Core
{
    namespace Loader
    {
        static Core::Resources::Mesh ParseOBJFile(const std::string& file_path);                                // Parse the .obj file and get the Mesh
        static std::map<std::string, Core::Resources::Material> ParseMTLFile(const std::string& file_path);     // Parse the .mtl file and get the materials
    }
}

#endif // OBJ_LOADER_H