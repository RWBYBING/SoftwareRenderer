#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <map>
#include <memory>

#include <core/resources/mesh.h>

namespace Core
{
    namespace Loader
    {
        void ParseOBJFile(const std::string& file_path, std::shared_ptr<Core::Resources::Mesh> mesh);                                // Parse the .obj file and get the Mesh
        // static std::map<std::string, Core::Resources::Material> ParseMTLFile(const std::string& file_path);     // Parse the .mtl file and get the materials
    }
}

#endif // OBJ_LOADER_H