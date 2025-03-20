#ifndef VERTEX_PROCESSING_H
#define VERTEX_PROCESSING_H

#include <memory>
#include <vector>

#include <core/math/matrix.h>
#include <core/primitives/vertex.h>
#include <core/resources/camera.h>
#include <core/resources/mesh.h>

namespace Core
{
    namespace Pipeline
    {
        class VertexProcessing
        {
        public:
            VertexProcessing();
            ~VertexProcessing();

            // Transform Vertex
            std::vector<Core::Primitives::Vertex> TransformMesh() const;
        };
    }
}

#endif // VERTEX_PROCESSING_H