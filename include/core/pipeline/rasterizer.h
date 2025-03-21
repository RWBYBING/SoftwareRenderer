#ifndef RASTERIZER_H
#define RASTERIXER_H

#include <memory>
#include <vector>

#include <core/buffer/framebuffer.h>
#include <core/buffer/depthbuffer.h>
#include <core/primitives/fragment.h>
#include <core/primitives/triangle.h>

namespace Core
{
    namespace Pipeline
    {
        class Rasterizer
        {
        public:
            Rasterizer();
            ~Rasterizer();

            // Set Buffer
            void SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer);
            void SetDepthBuffer(std::shared_ptr<Core::Buffer::DepthBuffer> buffer);

            // Rasterization processing
            std::vector<Core::Primitives::Fragment> RasterizeTriangle(const Core::Primitives::Triangle& tri) const;
            bool DepthTest(const Core::Primitives::Fragment& frag) const;

        private:
            // calculate the bounding box
            void CalculateBoundingBox(const Core::Primitives::Triangle& tri, int& min_x, int& max_x, int& min_y, int& max_y) const;
            // calculate the barycentric coordinates (for interpolating)
            bool BarycentricCoordinates(
                const Core::Math::Vector2& P,
                const Core::Math::Vector2& A,
                const Core::Math::Vector2& B,
                const Core::Math::Vector2& C,
                float& alpha,
                float& beta,
                float& gamma
            ) const;
            // Interpolate
            Core::Primitives::Fragment InterpolateFragment(const Core::Primitives::Triangle& tri, float alpha, float beta, float gamma) const;


        private:
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer;    // frame buffer
            std::shared_ptr<Core::Buffer::DepthBuffer> depth_buffer;    // depth buffer
        };
    }
}

#endif // RASTERIZER_H