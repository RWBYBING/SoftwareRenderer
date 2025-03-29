#ifndef CORE_PIPELINE_FRAMEBUFFER_OPERATION_H
#define CORE_PIPELINE_FRAMEBUFFER_OPERATION_H

#include <vector>
#include <memory>

#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/blocked_range2d.h>

#include <core/basic/primitives.h>
#include <core/buffer/framebuffer.h>
#include <core/buffer/depthbuffer.h>

// namespace Pipeline
// {
//     class FrameBufferOperation
//     {
//     public:
//         FrameBufferOperation();
//         ~FrameBufferOperation();

//         // Set Buffer
//         void SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer);
//         void SetDepthBuffer(std::shared_ptr<Buffer::DepthBuffer> buffer);

//         void WriteFragment2Buffer(const tbb::concurrent_vector<Primitives::Fragment>& fragments);

//     private:
//         // Depth Test
//         bool DepthTest(int x, int y, float depth) const;

//     private:
//         std::shared_ptr<Buffer::FrameBuffer> frame_buffer_ptr;
//         std::shared_ptr<Buffer::DepthBuffer> depth_buffer_ptr;
//     };
// }

#endif // CORE_PIPELINE_FRAMEBUFFER_OPERATION_H