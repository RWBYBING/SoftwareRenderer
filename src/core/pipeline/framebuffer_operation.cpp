#include <core/pipeline/framebuffer_operation.h>

#include <iostream>

using namespace Core::Pipeline;

FrameBufferOperation::FrameBufferOperation()
    : frame_buffer_ptr{nullptr}
    , depth_buffer_ptr{nullptr}
{

}

FrameBufferOperation::~FrameBufferOperation()
{

}

void FrameBufferOperation::SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer)
{
    this->frame_buffer_ptr = buffer;
}

void FrameBufferOperation::SetDepthBuffer(std::shared_ptr<Core::Buffer::DepthBuffer> buffer)
{
    this->depth_buffer_ptr = buffer;
}

void FrameBufferOperation::WriteFragment2Buffer(const std::vector<Core::Primitives::Fragment>& fragments)
{
    for (auto& fragment : fragments)
    {
        int x = fragment.x;
        int y = fragment.y;

        float depth = fragment.depth;

        // If pass the depth test, write new color into frame buffer
        if (this->DepthTest(x, y, depth))
        {
            this->frame_buffer_ptr->SetPixel(x, y, fragment.color);
        }
    }
}

bool FrameBufferOperation::DepthTest(int x, int y, float depth) const
{
    float current_depth = this->depth_buffer_ptr->GetDepth(x, y);

    if (depth > current_depth)
    {
        this->depth_buffer_ptr->SetDepth(x, y, depth);
        return true;
    }

    return false;
}