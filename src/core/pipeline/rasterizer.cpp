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

void Rasterizer::CalculateBoundingBox(const Core::Primitives::Triangle& tri, int& min_x, int& max_x, int& min_y, int& max_y) const
{
    // calculate the board
    min_x = static_cast<int>(std::floorf(std::min({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x})));
    max_x = static_cast<int>(std::ceilf(std::max({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x})));
    min_y = static_cast<int>(std::floorf(std::min({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y})));
    max_y = static_cast<int>(std::ceilf(std::max({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y})));

    // constrain the board in the screen area
    min_x = std::max(min_x, 0);
    max_x = std::min(max_x, this->frame_buffer->GetWidth() - 1);
    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, this->frame_buffer->GetHeight() - 1);
}

bool Rasterizer::BarycentricCoordinates(
    const Core::Math::Vector2& P,
    const Core::Math::Vector2& A,
    const Core::Math::Vector2& B,
    const Core::Math::Vector2& C,
    float& alpha,
    float& beta,
    float& gamma
) const
{
    Core::Math::Vector2 AB = B - A;
    Core::Math::Vector2 AC = C - A;
    Core::Math::Vector2 AP = P - A;

    // Calculate area ratio
    float areaABC = AB.Cross(AC);   // The double area of ​​the numerator and denominator cancels out, so there is no need to explicitly divide by 2.
    if (areaABC == 0) { return false; }

    float areaPBC = (B - P).Cross(C - P);
    float areaPCA = (C - P).Cross(A - P);
    alpha = areaPBC / areaABC;
    beta = areaPCA / areaABC;
    gamma = 1.0f - alpha - beta;

    return (alpha > 0) && (beta > 0) && (gamma > 0);
}

Core::Primitives::Fragment Rasterizer::InterpolateFragment(const Core::Primitives::Triangle& tri, float alpha, float beta, float gamma) const
{
    Core::Primitives::Fragment fragment;

    
}

// std::vector<Core::Primitives::Fragment> Rasterizer::RasterizeTriangle(const Core::Primitives::Triangle& tri) const
// {
//     std::vector<Core::Primitives::Fragment> fragments;

//     // Calculate the bounding box
//     float min_x = std::min({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x});
//     float max_x = std::max({tri.vertices[0].pos.x, tri.vertices[1].pos.x, tri.vertices[2].pos.x});
//     float min_y = std::min({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y});
//     float max_y = std::max({tri.vertices[0].pos.y, tri.vertices[1].pos.y, tri.vertices[2].pos.y});

//     // Iterate all the pixels in the bounding box
//     for (int y = static_cast<int>(min_y); y <= static_cast<int>(max_y); ++y)
//     {
//         for (int x = static_cast<int>(min_x); x <= static_cast<int>(max_x); ++x)
//         {
//             // TODO
//         }
//     }

//     return fragments;
// }

// bool Rasterizer::DepthTest(const Core::Primitives::Fragment& frag) const
// {
//     if (!this->depth_buffer)
//     {
//         return false;
//     }

//     float current_depth = this->depth_buffer->GetDepth(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y));
//     if (frag.pos.z < current_depth)
//     {
//         this->depth_buffer->SetDepth(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y), frag.pos.z);
//         return true;
//     }
//     return false;
// }

// void Rasterizer::WriteToFrameBuffer(const Core::Primitives::Fragment& frag)
// {
//     if (this->frame_buffer) 
//     {
//         this->frame_buffer->SetPixel(static_cast<int>(frag.pos.x), static_cast<int>(frag.pos.y), frag.color);
//     }
// }

