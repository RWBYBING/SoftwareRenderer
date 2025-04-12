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
    , material_ptr{nullptr}
    , light_ptr{nullptr}
    , camera_ptr{nullptr}
{
    msaa_sample_offsets = {
        { 0.25f, 0.25f },  // Bottom-left
        { 0.75f, 0.25f },  // Bottom-right
        { 0.75f, 0.75f },  // Top-right
        { 0.25f, 0.75f }   // Top-left
    };
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

void Rasterizer::SetCamera(std::shared_ptr<Resources::PerspectiveCamera> camera)
{
    this->camera_ptr = camera;
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
        if (anti_aliasing_mode == AntiAliasingMode::None)
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
                        for (int y = min_y; y < max_y; ++y)
                        {
                            for (int x = min_x; x < max_x; ++x)
                            {
                                Vector2 P(x + 0.5f, y + 0.5f);
                                float alpha, beta, gamma;
                                // Determine if this pixel is inside the triangle
                                if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                                {
                                    // construct the fragment through interpolation
                                    auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);

                                    // Phong shading
                                    if (shading_mode == ShadingMode::Phong)
                                    {
                                        this->PhongShading(fragment);
                                    }

                                    // Z-Buffering
                                    if (this->DepthTest(fragment.x, fragment.y, fragment.depth))
                                    {
                                        this->WriteFragment2Buffer(fragment);
                                    }
                                }
                            }
                        }
                    }
                }
            );
        }

        else if (anti_aliasing_mode == AntiAliasingMode::MSAA_WITH_BLACK_EDGE)
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

                        for (int y = min_y; y < max_y; ++y)
                        {
                            for (int x = min_x; x < max_x; ++x)
                            {
                                int num = 0;
                                float alpha, beta, gamma;
                                for (int k = 0; k < 4; ++k)
                                {
                                    Vector2 P(x + msaa_sample_offsets[k].x, y + msaa_sample_offsets[k].y);
                                    if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                                    {
                                        num++;
                                    }
                                }

                                if (num > 0)
                                {
                                    // construct the fragment through interpolation
                                    auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);

                                    // Phong shading
                                    if (shading_mode == ShadingMode::Phong)
                                    {
                                        this->PhongShading(fragment);
                                    }
                    
                                    // Z-Buffering
                                    if (this->DepthTest(fragment.x, fragment.y, fragment.depth))
                                    {
                                        fragment.color.x = fragment.color.x * num * 0.25;
                                        fragment.color.y = fragment.color.y * num * 0.25;
                                        fragment.color.z = fragment.color.z * num * 0.25;
                                        this->WriteFragment2Buffer(fragment);
                                    }
                                }
                            }
                        }
                    }
                }
            );
        }

        else if (anti_aliasing_mode == AntiAliasingMode::MSAA_NO_BLACK_EDGE)
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

                        // Pass 1
                        for (int y = min_y; y < max_y; ++y)
                        {
                            for (int x = min_x; x < max_x; ++x)
                            {
                                float alpha, beta, gamma;
                                for (int k = 0; k < 4; ++k)
                                {
                                    Vector2 P(x + msaa_sample_offsets[k].x, y + msaa_sample_offsets[k].y);
                                    if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                                    {
                                        // construct the fragment through interpolation
                                        auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);
                                        // float depth = this->InterpolateDepth(triangles[i], alpha, beta, gamma);
                                        this->depth_buffer->SetSample(x, y, k, fragment.depth);
                                    }
                                }

                                
                            }
                        }

                        // // Pass 2
                        // for (int y = min_y; y < max_y; ++y)
                        // {
                        //     for (int x = min_x; x < max_x; ++x)
                        //     {
                        //         float alpha, beta, gamma;
                        //         Vector2 P(x + 0.5, y + 0.5);
                        //         if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                        //         {
                        //             // construct the fragment through interpolation
                        //             auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);
                                    
                        //             int num = this->depth_buffer->GetCoverage(x, y, fragment.depth);

                        //             if (num > 0)
                        //             {
                        //                 // Phong shading
                        //                 if (shading_mode == ShadingMode::Phong)
                        //                 {
                        //                     this->PhongShading(fragment);
                        //                 }

                        //                 Color background_color = this->frame_buffer->GetPixel(x, y);
                        //                 fragment.color = fragment.color * (num / 4.0f) + background_color * (1.0f - num / 4.0f);
                        //                 // fragment.color.x = fragment.color.x * num * 0.25;
                        //                 // fragment.color.y = fragment.color.y * num * 0.25;
                        //                 // fragment.color.z = fragment.color.z * num * 0.25;
                        //                 this->WriteFragment2Buffer(fragment);
                        //             }
                        //         }
                        //     }
                        // }
                    }
                }
            );
        }

        // FXAA
        if (anti_aliasing_mode == AntiAliasingMode::FXAA)
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
                        for (int y = min_y; y < max_y; ++y)
                        {
                            for (int x = min_x; x < max_x; ++x)
                            {
                                Vector2 P(x + 0.5f, y + 0.5f);
                                float alpha, beta, gamma;
                                // Determine if this pixel is inside the triangle
                                if (this->BarycentricCoordinates(P, screen_pos[0], screen_pos[1], screen_pos[2], alpha, beta, gamma))
                                {
                                    // construct the fragment through interpolation
                                    auto fragment = this->InterpolateFragment(triangles[i], alpha, beta, gamma, x, y);

                                    // Phong shading
                                    if (shading_mode == ShadingMode::Phong)
                                    {
                                        this->PhongShading(fragment);
                                    }

                                    // Z-Buffering
                                    if (this->DepthTest(fragment.x, fragment.y, fragment.depth))
                                    {
                                        this->WriteFragment2Buffer(fragment);
                                    }
                                }
                            }
                        }
                    }
                }
            );

            this->frame_buffer->ApplyFXAA();
        }
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

    // normal interpolation
    fragment.normal = tri.v0.normal * alpha
                    + tri.v1.normal * beta
                    + tri.v2.normal * gamma;

    return fragment;
}

float Rasterizer::InterpolateDepth(const Primitives::Triangle& tri, float alpha, float beta, float gamma) const
{
    return alpha * tri.v0.pos.z + beta * tri.v1.pos.z + gamma * tri.v2.pos.z;
}

void Rasterizer::PhongShading(Primitives::Fragment& frag) const
{
    Vector3 view_dir = -glm::normalize(this->camera_ptr->look_at);
    Vector3 light_dir = -glm::normalize(this->light_ptr->dir);

    // Normalize the normal
    frag.normal = glm::normalize(frag.normal);

    // ambient
    Color ambient = this->light_ptr->ambient_intensity * this->material_ptr->diffuse_color;

    // diffuse
    float diff = std::max(0.0f, glm::dot(frag.normal, light_dir));
    Color diffuse = this->light_ptr->diffuse_intensity * (material_ptr->diffuse_color * diff);

    // highlight
    Vector3 halfway_dir = glm::normalize(light_dir + view_dir);
    float spec = std::pow(std::max(0.0f, glm::dot(frag.normal, halfway_dir)), material_ptr->shininess);
    Color specular = this->light_ptr->specular_intensity * (this->material_ptr->specular_color * spec);

    Color final_color = ambient + diffuse + specular;

    final_color.r = glm::clamp(final_color.r, 0.0f, 1.0f);
    final_color.g = glm::clamp(final_color.g, 0.0f, 1.0f);
    final_color.b = glm::clamp(final_color.b, 0.0f, 1.0f);
    final_color.a = 1.0f;

    frag.color = final_color;
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