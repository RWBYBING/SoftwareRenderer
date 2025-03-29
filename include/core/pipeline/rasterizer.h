#ifndef CORE_PIPELINE_RASTERIZER_H
#define CORE_PIPELINE_RASTERIXER_H

#include <memory>
#include <vector>

#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/blocked_range2d.h>

#include <core/buffer/framebuffer.h>
#include <core/buffer/depthbuffer.h>
#include <core/basic/primitives.h>

namespace Pipeline
{
    class Rasterizer
    {
    public:
        Rasterizer();
        ~Rasterizer();

        // Set Buffer
        void SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer);
        void SetDepthBuffer(std::shared_ptr<Buffer::DepthBuffer> buffer);

        // Rasterization processing
        void RasterizeTriangle(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices);
        void RasterizeLineFrame(const std::vector<Primitives::Vertex>& vertices);
        void RasterizeVertex(const std::vector<Primitives::Vertex>& vertices);

    private:
        void WriteFragment2Buffer(const Primitives::Fragment& fragment);

    // vertices rasterization
    private:
        // Construct a single fragment for a vertex
        

    // lineframe rasterization
    private:

    // triangle rasterization
    private:
        // triangle assembly
        std::vector<Primitives::Triangle> TriangleAssembly(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices) const;
        // calculate the bounding box
        void CalculateBoundingBox(const Primitives::Triangle& tri, int& min_x, int& max_x, int& min_y, int& max_y) const;
        // // calculate the barycentric coordinates (for interpolating)
        bool BarycentricCoordinates(
            const Vector2& P,
            const Vector2& A,
            const Vector2& B,
            const Vector2& C,
            float& alpha,
            float& beta,
            float& gamma
        ) const;
        // Interpolate
        Primitives::Fragment InterpolateFragment(const Primitives::Triangle& tri, float alpha, float beta, float gamma, int x, int y) const;
        // Depth Test
        bool DepthTest(int x, int y, float depth) const;


    private:
        std::shared_ptr<Buffer::FrameBuffer> frame_buffer;    // frame buffer
        std::shared_ptr<Buffer::DepthBuffer> depth_buffer;    // depth buffer
    };
}

#endif // CORE_PIPELINE_RASTERIXER_H