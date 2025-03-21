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

            void SetModelMatrix(const Core::Math::Matrix4x4& mat);
            void SetViewMatrix(const Core::Math::Matrix4x4& mat);
            void SetProjectionMatrix(const Core::Math::Matrix4x4& mat);

            // Transform Vertices
            std::vector<Core::Primitives::Vertex> TransformVertices(const std::vector<Core::Primitives::Vertex>& vertices) const;

        private:
            Core::Math::Matrix4x4 model_matrix;
            Core::Math::Matrix4x4 view_matrix;
            Core::Math::Matrix4x4 projection_matrix;
        };
    }
}

#endif // VERTEX_PROCESSING_H