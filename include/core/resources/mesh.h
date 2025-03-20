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

            void AddVertex(const Core::Primitives::Vertex vert);        // Add a new vertex into our mesh object
            void AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2);    // Add three indices of the vertex

            Mesh();
            ~Mesh();
        };
    }
}

#endif // MESH_H