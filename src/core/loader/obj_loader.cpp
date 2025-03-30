#include <core/loader/obj_loader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace Loader;

void Loader::ParseOBJFile(const std::string& file_path, std::shared_ptr<Resources::Mesh> mesh)
{
    std::vector<Vector3> temp_positions;
    std::vector<uint32_t> temp_indices;
    
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open OBJ file: " + file_path);
    }

    std::string line;
    while (std::getline(file, line)) {
        // skip the empty line and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        
        // Parse the vertex position
        if (prefix == "v") 
        {
            float x, y, z;
            iss >> x >> y >> z;
            Primitives::Vertex vertex;
            vertex.pos = Vector4(x, y, z, 1.0f);
            mesh->AddVertex(vertex);
        }

        // Parse the faces
        else if (prefix == "f") 
        {
            uint32_t a, b, c;
            iss >> a >> b >> c;
            mesh->AddTriangle(a - 1, b - 1, c - 1);
        }
    }
}