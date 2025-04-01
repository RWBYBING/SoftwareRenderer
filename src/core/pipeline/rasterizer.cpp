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

void Rasterizer::SetMaterial(std::shared_ptr<Resources::Material> material)
{
    this->material_ptr = material;
}

void Rasterizer::SetLight(std::shared_ptr<Resources::Light> light)
{
    this->light_ptr = light;
}

void Rasterizer::Rasterize(
    const std::vector<Primitives::Triangle>& triangles,
    const RenderingMode rendering_mode,
    const ShadingMode shading_mode,
    const AntiAliasingMode anti_aliasing_mode
)
{
    if (rendering_mode == RenderingMode::Vertex)
    {
        for (auto triangle : triangles)
        {
            auto fragment_0 = this->ConstructFragment(triangle.v0);
            auto fragment_1 = this->ConstructFragment(triangle.v1);
            auto fragment_2 = this->ConstructFragment(triangle.v2);

            this->WriteFragment2Buffer(fragment_0);
            this->WriteFragment2Buffer(fragment_1);
            this->WriteFragment2Buffer(fragment_2);
        }
    }

    else if (rendering_mode == RenderingMode::LineFrame)
    {
        for (auto triangle : triangles)
        {
            this->BresenhamLine(triangle.v0.pos.x, triangle.v0.pos.y, triangle.v1.pos.x, triangle.v1.pos.y);
            this->BresenhamLine(triangle.v1.pos.x, triangle.v1.pos.y, triangle.v2.pos.x, triangle.v2.pos.y);
            this->BresenhamLine(triangle.v2.pos.x, triangle.v2.pos.y, triangle.v0.pos.x, triangle.v0.pos.y);
        }
    }

    else if (rendering_mode == RenderingMode::Triangles)
    {
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
    }
}

Primitives::Fragment Rasterizer::ConstructFragment(const Primitives::Vertex vertex)
{
    Primitives::Fragment fragment;

    fragment.x = vertex.pos.x;
    fragment.y = vertex.pos.y;
    fragment.color = vertex.color;
    fragment.depth = vertex.pos.z;

    return fragment;
}

void Rasterizer::BresenhamLine(int x0, int y0, int x1, int y1)
{
    // 1. check if the slope > 1
    bool steep = abs(y1 - y0) > abs(x1 - x0);

    // 2. exchange x and y for making the slope <= 1
    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    // 3. making sure the line is being drew from left to right
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int err = dx / 2; // initial error
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            Primitives::Fragment fragment;

            fragment.x = y;
            fragment.y = x;
            fragment.color = Color(1.0f, 1.0f, 1.0f, 1.0f);

            this->WriteFragment2Buffer(fragment);
        } else {
            Primitives::Fragment fragment;

            fragment.x = x;
            fragment.y = y;
            fragment.color = Color(1.0f, 1.0f, 1.0f, 1.0f);

            this->WriteFragment2Buffer(fragment);
        }
        err -= dy;
        if (err < 0) {
            y += ystep;
            err += dx;
        }
    }
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