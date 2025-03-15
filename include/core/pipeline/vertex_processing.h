#ifndef VERTEX_PROCESSING_H
#define VERTEX_PROCESSING_H

#include <core/math/matrix.h>
#include <core/primitives/vertex.h>

namespace Core
{
    namespace Pipeline
    {
        class VertexProcessing
        {
        public:
            VertexProcessing();
            ~VertexProcessing();

            // Set MVP Matrix
            void SetModelMatrix(const Core::Math::Matrix4x4& mat);
            void SetViewMatrix(const Core::Math::Matrix4x4& mat);
            void SetProjectionMatrix(const Core::Math::Matrix4x4& mat);

            // Transform Vertex
            Core::Primitives::Vertex TransformVertex(const Core::Primitives::Vertex& vert) const;

        private:
            Core::Math::Matrix4x4 model_matrix;                 // Transform vertices from model space to world space
            Core::Math::Matrix4x4 view_matrix;                  // Transform vertices from world space to camera space
            Core::Math::Matrix4x4 projection_matrix;            // Transform vertices from camera space to clip space
        };
    }
}

#endif // VERTEX_PROCESSING_H