#ifndef CORE_PIPELINE_VERTEX_PROCESSING_H
#define CORE_PIPELINE_VERTEX_PROCESSING_H

#include <memory>
#include <vector>

#include <core/basic/primitives.h>
#include <core/basic/resources.h>
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

        // Set All instances which evolved with the vertex processing
        void SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer);
        void SetMaterial(std::shared_ptr<Resources::Material> material);
        void SetLight(std::shared_ptr<Resources::Light> light);
        void SetCamera(std::shared_ptr<Resources::PerspectiveCamera> camera);

        // Transform Vertices
        std::vector<Primitives::Triangle> TransformVertices(
            const std::vector<Primitives::Vertex>& vertices,
            const std::vector<uint32_t>& indices,
            const RenderingMode rendering_mode,
            const ShadingMode shading_mode,
            const AntiAliasingMode anti_aliasing_mode,
            const bool enable_backface_culling,
            const bool enable_frustum_clipping
        ) const;

    private:
        // Backface culling
        bool IsBackface(const Primitives::Triangle& triangle) const;
        // Frustum clipping
        bool IsInsideViewFrustum(const Primitives::Vertex& vertex) const;
        // NDC transformation
        void NDC(Primitives::Vertex& vertex) const;
        // Map to screen space
        void ViewportTransformation(Primitives::Vertex& vertex) const;
        // Calculate the normal of the triangle and vertices
        void CalculateTriangleNormal(Primitives::Triangle& triangle) const;
        void CalculateVerticesNormal(std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices) const;
        // Flat Shading
        void FlatShading(Primitives::Triangle& triangle) const;
        // Gourand Shading
        void GourandShading(Primitives::Vertex& vertex) const;

    private:
        Matrix4x4 model_matrix;
        Matrix4x4 view_matrix;
        Matrix4x4 projection_matrix;

    private:
        std::shared_ptr<Buffer::FrameBuffer> frame_buffer;          // frame buffer
        std::shared_ptr<Resources::Material> material_ptr;          // material
        std::shared_ptr<Resources::Light> light_ptr;                // light
        std::shared_ptr<Resources::PerspectiveCamera> camera_ptr;   // camera
    };
}

#endif // CORE_PIPELINE_VERTEX_PROCESSING_H