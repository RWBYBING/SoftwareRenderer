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
#include <core/basic/resources.h>

namespace Pipeline
{
    class Rasterizer
    {
    public:
        Rasterizer();
        ~Rasterizer();

        // Set Instances
        void SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer);
        void SetDepthBuffer(std::shared_ptr<Buffer::DepthBuffer> buffer);
        void SetMaterial(std::shared_ptr<Resources::Material> material);
        void SetLight(std::shared_ptr<Resources::Light> light);

        // Rasterization processing
        void Rasterize(
            const std::vector<Primitives::Triangle>& triangles,
            const RenderingMode rendering_mode,
            const ShadingMode shading_mode,
            const AntiAliasingMode anti_aliasing_mode
        );

    private:
        void WriteFragment2Buffer(const Primitives::Fragment& fragment);

    // vertices rasterization
    private:
        // Construct a single fragment for a vertex
        Primitives::Fragment ConstructFragment(const Primitives::Vertex vertex);

    // lineframe rasterization
    private:
        // Bresenham‘s Line Algorithm
        void BresenhamLine(int x0, int y0, int x1, int y1);

    // triangle rasterization
    private:
        // calculate the bounding box
        void CalculateBoundingBox(const Primitives::Triangle& tri, int& min_x, int& max_x, int& min_y, int& max_y) const;
        // calculate the barycentric coordinates (for interpolating)
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
        std::shared_ptr<Buffer::FrameBuffer> frame_buffer;      // frame buffer
        std::shared_ptr<Buffer::DepthBuffer> depth_buffer;      // depth buffer
        std::shared_ptr<Resources::Material> material_ptr;      // material
        std::shared_ptr<Resources::Light> light_ptr;            // light
    };
}

#endif // CORE_PIPELINE_RASTERIXER_H

