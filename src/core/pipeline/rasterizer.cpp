#include <core/pipeline/rasterizer.h>

#include <utils/timer.h>

#include <algorithm>

using namespace Pipeline;

inline float cross2D(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}

Rasterizer::Rasterizer()
    : frame_buffer{nullptr}
    , depth_buffer{nullptr}
{

}

Rasterizer::~Rasterizer() = default;

void Rasterizer::SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer)
{
    this->frame_buffer = buffer;
}

void Rasterizer::SetDepthBuffer(std::shared_ptr<Buffer::DepthBuffer> buffer)
{
    this->depth_buffer = buffer;
}

void Rasterizer::RasterizeTriangle(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices)
{
    // assemble triangles
    auto triangles = this->TriangleAssembly(vertices, indices);

    // process triangle parallelly
    tbb::parallel_for(tbb::blocked_range<size_t>(0, triangles.size()),
        [&](const tbb::blocked_range<size_t>& range) {
            for (size_t i = range.begin(); i != range.end(); ++i) {
                // Get screen pos for each vertex in the triangle
                Vector2 screen_pos[3] = {
                    Vector2{triangles[i].v0.pos.x, triangles[i].v0.pos.y},
                    Vector2{triangles[i].v1.pos.x, triangles[i].v1.pos.y},
                    Vector2{triangles[i].v2.pos.x, triangles[i].v2.pos.y},
                };
                
                // calculate the bounding box
                int min_x, max_x, min_y, max_y;
                this->CalculateBoundingBox(triangles[i], min_x, max_x, min_y, max_y);

                // iterate all the pixel in the bounding box
                tbb::parallel_for(tbb::blocked_range2d<int>(min_y, max_y, min_x, max_x),
                    [&](const tbb::blocked_range2d<int>& range) {
                        for (int y = range.rows().begin(); y != range.rows().end(); ++y) {
                            for (int x = range.cols().begin(); x != range.cols().end(); ++x) {
                                Vector2 P(x + 0.5f, y + 0.5f);
                                float alpha, beta, gamma;
                                // Determine if this pixel is inside the triangle
                                if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                                {
                                    // construct the fragment through interpolation
                                    auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);

                                    // Z-Buffering
                                    if (this->DepthTest(fragment.x, fragment.y, fragment.depth))
                                    {
                                        this->WriteFragment2Buffer(fragment);
                                    }
                                }
                            }
                        }
                    }
                );
            }
        }
    );

    // size_t total_pixels = 0;
    // for (auto& triangle : triangles)
    // {
    //     Vector2 screen_pos[3] = {
    //         Vector2{triangle.v0.pos.x, triangle.v0.pos.y},
    //         Vector2{triangle.v1.pos.x, triangle.v1.pos.y},
    //         Vector2{triangle.v2.pos.x, triangle.v2.pos.y},
    //     };
        
    //     int min_x, max_x, min_y, max_y;
    //     this->CalculateBoundingBox(triangle, min_x, max_x, min_y, max_y);
    //     total_pixels += (max_x - min_x) * (max_y - min_y);
    //     // std::cout << min_x << ", " << max_x << ", " << min_y << ", " << max_y << std::endl;

    //     for (int y = min_y; y < max_y; ++y)
    //     {
    //         for (int x = min_x; x <= max_x; ++x)
    //         {
    //             // Vector2 P(x + 0.5f, y + 0.5f);
    //             // float alpha, beta, gamma;
    //             // if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma)) {
    //                 // fragments.emplace_back(
    //                     // this->InterpolateFragment(triangle, alpha, beta, gamma, x, y);
    //                 // );
    //             // }
    //         }
    //     }
    // }
    // std::cout << "Total Pixels to Process: " << total_pixels << std::endl;
}

void Rasterizer::RasterizeLineFrame(const std::vector<Primitives::Vertex>& vertices)
{

}

void Rasterizer::RasterizeVertex(const std::vector<Primitives::Vertex>& vertices)
{
    for (auto vertex : vertices)
    {
        
    }
}


















std::vector<Primitives::Triangle> Rasterizer::TriangleAssembly(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices) const
{
    std::vector<Primitives::Triangle> triangles;
    triangles.reserve(indices.size() / 3 + 1);

    for (size_t i = 0; i < indices.size(); i += 3) {
        Primitives::Triangle triangle;
        triangle.v0 = vertices[indices[i]];
        triangle.v1 = vertices[indices[i + 1]];
        triangle.v2 = vertices[indices[i + 2]];
        triangles.push_back(triangle);
    }

    return triangles;
}

void Rasterizer::CalculateBoundingBox(const Primitives::Triangle& tri, int& min_x, int& max_x, int& min_y, int& max_y) const
{
    // calculate the board
    min_x = static_cast<int>(std::floorf(std::min({tri.v0.pos.x, tri.v1.pos.x, tri.v2.pos.x})));
    max_x = static_cast<int>(std::ceilf(std::max({tri.v0.pos.x, tri.v1.pos.x, tri.v2.pos.x})));
    min_y = static_cast<int>(std::floorf(std::min({tri.v0.pos.y, tri.v1.pos.y, tri.v2.pos.y})));
    max_y = static_cast<int>(std::ceilf(std::max({tri.v0.pos.y, tri.v1.pos.y, tri.v2.pos.y})));

    // constrain the board in the screen area
    min_x = std::max(min_x, 0);
    max_x = std::min(max_x, this->frame_buffer->GetWidth() - 1);
    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, this->frame_buffer->GetHeight() - 1);
}

bool Rasterizer::BarycentricCoordinates(
    const Vector2& P,
    const Vector2& A,
    const Vector2& B,
    const Vector2& C,
    float& alpha,
    float& beta,
    float& gamma
) const
{
    // Calculate area ratio
    float areaABC = cross2D(B - A, C - A);   // The double area of ​​the numerator and denominator cancels out, so there is no need to explicitly divide by 2.
    if (areaABC == 0) { return false; }

    float areaPBC = cross2D(B - P, C - P);
    float areaPCA = cross2D(C - P, A - P);
    alpha = areaPBC / areaABC;
    beta = areaPCA / areaABC;
    gamma = 1.0f - alpha - beta;

    return (alpha > 0) && (beta > 0) && (gamma > 0);
}

Primitives::Fragment Rasterizer::InterpolateFragment(const Primitives::Triangle& tri, float alpha, float beta, float gamma, int x, int y) const
{
    Primitives::Fragment fragment;
    fragment.x = x;
    fragment.y = y;

    // depth interpolation
    fragment.depth = alpha * tri.v0.pos.z
                   + beta * tri.v1.pos.z
                   + gamma * tri.v2.pos.z;

    // color interpolation
    fragment.color = tri.v0.color * alpha
                   + tri.v1.color * beta
                   + tri.v2.color * gamma;

    return fragment;
}

void Rasterizer::WriteFragment2Buffer(const Primitives::Fragment& fragment)
{
    this->frame_buffer->SetPixel(fragment.x, fragment.y, fragment.color);
}

bool Rasterizer::DepthTest(int x, int y, float depth) const
{
    float current_depth = this->depth_buffer->GetDepth(x, y);

    if (depth > current_depth && depth < 1.0f)
    {
        this->depth_buffer->SetDepth(x, y, depth);
        return true;
    }

    return false;
}