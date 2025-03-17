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
            void WriteToFrameBuffer(const Core::Primitives::Fragment& frag);

        
        private:
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer;    // frame buffer
            std::shared_ptr<Core::Buffer::DepthBuffer> depth_buffer;    // depth buffer

            // bool InsideTriangle(const Core::Primitives::Triangle& tri, int x, int y);   // Determine if a fragment is inside a triangle
        };
    }
}

#endif // RASTERIZER_H