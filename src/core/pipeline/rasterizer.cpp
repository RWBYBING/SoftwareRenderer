#include <core/pipeline/rasterizer.h>

#include <algorithm>

using namespace Core::Pipeline;

Rasterizer::Rasterizer()
    : frame_buffer{nullptr}
    , depth_buffer{nullptr}
{

}

Rasterizer::~Rasterizer()
{

}

void Rasterizer::SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer)
{
    this->frame_buffer = buffer;
}

void Rasterizer::SetDepthBuffer(std::shared_ptr<Core::Buffer::DepthBuffer> buffer)
{
    this->depth_buffer = buffer;
}

std::vector<Core::Primitives::Fragment> Rasterizer::RasterizeTriangle(const Core::Primitives::Triangle& tri) const
{
    std::vector<Core::Primitives::Fragment> fragments;

    // Calculate the bounding box
    float min_x = std::min({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x});
    float max_x = std::max({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x});
    float min_y = std::min({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y});
    float max_y = std::max({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y});

    // Iterate all the pixels in the bounding box
    for (int y = static_cast<int>(min_y); y <= static_cast<int>(max_y); ++y)
    {
        for (int x = static_cast<int>(min_x); x <= static_cast<int>(max_x); ++x)
        {
            // TODO
        }
    }

    return fragments;
}

bool Rasterizer::DepthTest(const Core::Primitives::Fragment& frag) const
{
    if (!this->depth_buffer)
    {
        return false;
    }

    float current_depth = this->depth_buffer->GetDepth(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y));
    if (frag.pos.z < current_depth)
    {
        this->depth_buffer->SetDepth(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y), frag.pos.z);
        return true;
    }
    return false;
}

void Rasterizer::WriteToFrameBuffer(const Core::Primitives::Fragment& frag)
{
    if (this->frame_buffer) 
    {
        this->frame_buffer->SetPixel(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y), frag.color);
    }
}

// bool Rasterizer::InsideTriangle(const Core::Primitives::Triangle& tri, int x, int y)
// {
//     return true;
// }
