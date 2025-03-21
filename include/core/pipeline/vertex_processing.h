#ifndef VERTEX_PROCESSING_H
#define VERTEX_PROCESSING_H

#include <memory>
#include <vector>

#include <core/math/matrix.h>
#include <core/primitives/vertex.h>
#include <core/resources/camera.h>
#include <core/resources/mesh.h>
#include <core/buffer/framebuffer.h>

namespace Core
{
    namespace Pipeline
    {
        class VertexProcessing
        {
        public:
            VertexProcessing();
            ~VertexProcessing();

            void SetModelMatrix(const Core::Math::Matrix4x4& mat);          // From local space to world space
            void SetViewMatrix(const Core::Math::Matrix4x4& mat);           // From world space to view space
            void SetProjectionMatrix(const Core::Math::Matrix4x4& mat);     // From view space to clip space

            // Set Buffer (For getting the size of framebuffer for viewport transformation)
            void SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer);

            // Transform Vertices
            std::vector<Core::Primitives::Vertex> TransformVertices(const std::vector<Core::Primitives::Vertex>& vertices) const;

        private:
            void NDC(Core::Primitives::Vertex& vertex) const;
            void ViewportTransformation(Core::Primitives::Vertex& vertex) const;

        private:
            Core::Math::Matrix4x4 model_matrix;
            Core::Math::Matrix4x4 view_matrix;
            Core::Math::Matrix4x4 projection_matrix;

        private:
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer;    // frame buffer
        };
    }
}

#endif // VERTEX_PROCESSING_H