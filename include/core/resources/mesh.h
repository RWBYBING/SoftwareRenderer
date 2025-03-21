#ifndef MESH_H
#define MESH_H

#include <vector>
#include <cstdint>

#include <core/math/vector.h>
#include <core/math/matrix.h>
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

            Core::Math::Vector3 translation;                            // Translation coefficient on xyz direction
            Core::Math::Vector3 rotation;                               // Rotation coefficient on xyz direction
            Core::Math::Vector3 scale;                                  // Scale coefficient on xyz direction

            void AddVertex(const Core::Primitives::Vertex vert);        // Add a new vertex into our mesh object
            void AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2);    // Add three indices of the vertex

            Core::Math::Matrix4x4 GetModelMatrix() const;               // Get the model transformation matrix

            Mesh();
            ~Mesh();
        };
    }
}

#endif // MESH_H