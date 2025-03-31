#ifndef CORE_PIPELINE_VERTEX_PROCESSING_H
#define CORE_PIPELINE_VERTEX_PROCESSING_H

#include <memory>
#include <vector>

#include <core/basic/primitives.h>
#include <core/buffer/framebuffer.h>


namespace Pipeline
{
    class VertexProcessing
    {
    public:
        VertexProcessing();
        ~VertexProcessing();

        void SetModelMatrix(const Matrix4x4& mat);          // From local space to world space
        void SetViewMatrix(const Matrix4x4& mat);           // From world space to view space
        void SetProjectionMatrix(const Matrix4x4& mat);     // From view space to clip space

        // Set Buffer (For getting the size of framebuffer for viewport transformation)
        void SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer);

        // Transform Vertices
        std::vector<Primitives::Triangle> TransformVertices(
            const std::vector<Primitives::Vertex>& vertices,
            const std::vector<uint32_t>& indices,
            ShadingMode shading_mode
        ) const;

    private:
        // triangle assembly
        std::vector<Primitives::Triangle> TriangleAssembly(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices) const;
        // Backface culling
        bool IsBackface(const Primitives::Triangle& triangle) const;
        // Frustum clipping
        bool IsInsideViewFrustum(const Primitives::Vertex& vertex) const;
        // NDC transformation
        void NDC(Primitives::Vertex& vertex) const;
        // Map to screen space
        void ViewportTransformation(Primitives::Vertex& vertex) const;

    private:
        Matrix4x4 model_matrix;
        Matrix4x4 view_matrix;
        Matrix4x4 projection_matrix;

    private:
        std::shared_ptr<Buffer::FrameBuffer> frame_buffer;    // frame buffer
    };
}

#endif // CORE_PIPELINE_VERTEX_PROCESSING_H