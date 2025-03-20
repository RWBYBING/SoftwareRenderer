#ifndef MESH_H
#define MESH_H

#include <vector>

#include <core/primitives/vertex.h>
#include <core/resources/material.h>

namespace Core
{
    namespace Resources
    {
        struct Mesh
        {
        public:
            std::vector<Core::Primitives::Vertex> vertices;
            std::vector<u_int32_t> indices;
            Material material;

            Mesh();
            ~Mesh();
        };
    }
}

#endif // MESH_H