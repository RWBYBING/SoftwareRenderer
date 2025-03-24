#ifndef FRAMEBUFFER_OPERATION_H
#define FRAMEBUFFER_OPERATION_H

#include <vector>
#include <memory>

#include <core/primitives/fragment.h>
#include <core/buffer/framebuffer.h>
#include <core/buffer/depthbuffer.h>

namespace Core
{
    namespace Pipeline
    {
        class FrameBufferOperation
        {
        public:
            FrameBufferOperation();
            ~FrameBufferOperation();

            // Set Buffer
            void SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer);
            void SetDepthBuffer(std::shared_ptr<Core::Buffer::DepthBuffer> buffer);

            void WriteFragment2Buffer(const std::vector<Core::Primitives::Fragment>& fragments);

        private:
            // Depth Test
            bool DepthTest(int x, int y, float depth) const;

        private:
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer_ptr;
            std::shared_ptr<Core::Buffer::DepthBuffer> depth_buffer_ptr;
        };
    }
}

#endif // FRAMEBUFFER_OPERATION_H