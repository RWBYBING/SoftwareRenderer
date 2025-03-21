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

    // depth interpolation
    fragment.depth = alpha * tri.vertices[0].pos.z
                   + beta * tri.vertices[1].pos.z
                   + gamma * tri.vertices[2].pos.z;

    // color interpolation
    fragment.color = tri.vertices[0].color * alpha
                   + tri.vertices[1].color * beta
                   + tri.vertices[2].color * gamma;

    // texcoord interpolation
    fragment.texcoord = tri.vertices[0].texcoord * alpha
                      + tri.vertices[1].texcoord * beta
                      + tri.vertices[2].texcoord * gamma;

    return fragment;
}

std::vector<Core::Primitives::Fragment> Rasterizer::RasterizeTriangle(const std::vector<Core::Primitives::Triangle>& triangles) const
{
    std::vector<Core::Primitives::Fragment> fragments;

    for (auto& triangle : triangles)
    {
        // 1. Get the screen pos
        Core::Math::Vector2 screen_pos[3] = {
            Core::Math::Vector2{triangle.vertices[0].pos.x, triangle.vertices[0].pos.y},
            Core::Math::Vector2{triangle.vertices[1].pos.x, triangle.vertices[1].pos.y},
            Core::Math::Vector2{triangle.vertices[2].pos.x, triangle.vertices[2].pos.y},
        };

        // 2. calculate the bounding box
        int min_x, max_x, min_y, max_y;
        this->CalculateBoundingBox(triangle, min_x, max_x, min_y, max_y);

        // 3. iterate each pixel in the bounding box
        for (int y = min_y; y < max_y; ++y)
        {
            for (int x = min_x; x <= max_x; ++x)
            {
                Core::Math::Vector2 P(x + 0.5f, y + 0.5f); // Get the center of pixel
                // 4: calculate the barycentric coordinates
                float alpha, beta, gamma;
                if (!this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma)) 
                {
                    continue; // the pixel is outside of the triangle
                }

                Core::Primitives::Fragment fragment = this->InterpolateFragment(triangle, alpha, beta, gamma);
                fragments.push_back(fragment);
            }
        }
    }

    return fragments;
}
