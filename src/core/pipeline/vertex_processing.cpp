#include <core/pipeline/vertex_processing.h>

#include <iostream>
#include <cmath>

#include <glm/ext/matrix_transform.hpp> 

using namespace Pipeline;

VertexProcessing::VertexProcessing()
    : model_matrix{glm::identity<glm::mat4>()}
    , view_matrix{glm::identity<glm::mat4>()}
    , projection_matrix{glm::identity<glm::mat4>()}
    , frame_buffer{nullptr}
    , material_ptr{nullptr}
    , light_ptr{nullptr}
    , camera_ptr{nullptr}
{

}

VertexProcessing::~VertexProcessing() = default;

void VertexProcessing::SetModelMatrix(const Matrix4x4& mat)
{
    this->model_matrix = mat;
}

void VertexProcessing::SetViewMatrix(const Matrix4x4& mat)
{
    this->view_matrix = mat;
}

void VertexProcessing::SetProjectionMatrix(const Matrix4x4& mat)
{
    this->projection_matrix = mat;
}

void VertexProcessing::SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer)
{
    this->frame_buffer = buffer;
}

void VertexProcessing::SetMaterial(std::shared_ptr<Resources::Material> material)
{
    this->material_ptr = material;
}

void VertexProcessing::SetLight(std::shared_ptr<Resources::Light> light)
{
    this->light_ptr = light;
}

void VertexProcessing::SetCamera(std::shared_ptr<Resources::PerspectiveCamera> camera)
{
    this->camera_ptr = camera;
}

std::vector<Primitives::Triangle> VertexProcessing::TransformVertices(
    const std::vector<Primitives::Vertex>& vertices,
    const std::vector<uint32_t>& indices,
    const RenderingMode rendering_mode,
    const ShadingMode shading_mode,
    const AntiAliasingMode anti_aliasing_mode,
    const bool enable_backface_culling,
    const bool enable_frustum_clipping
) const 
{
    std::vector<Primitives::Vertex> temp_vertices = vertices;

    const auto mvp = projection_matrix * (view_matrix * model_matrix);

    // Apply MVP Matrix on each vertex, now all the vertices are in the clip space
    for (auto& vertex : temp_vertices)
    {
        vertex.pos = mvp * vertex.pos;
    }

    // Reserve memory for triangles
    std::vector<Primitives::Triangle> triangles;
    triangles.reserve(indices.size() / 3 + 1);

    // Only prepare all the vertex data
    if (rendering_mode == RenderingMode::Vertex)
    {
        // Assembly triangle
        for (size_t i = 0; i < indices.size(); i += 3) {
            Primitives::Triangle triangle;
            triangle.v0 = temp_vertices[indices[i]];
            triangle.v1 = temp_vertices[indices[i + 1]];
            triangle.v2 = temp_vertices[indices[i + 2]];

            triangles.push_back(triangle);
        }

        // Transform to the screen space
        for (auto& triangle : triangles)
        {
            // NDC
            this->NDC(triangle.v0);
            this->NDC(triangle.v1);
            this->NDC(triangle.v2);
    
            // Viewport transformation
            this->ViewportTransformation(triangle.v0);
            this->ViewportTransformation(triangle.v1);
            this->ViewportTransformation(triangle.v2);
        }
    }

    // Prepare the vertex data for lineframe
    else if (rendering_mode == RenderingMode::LineFrame)
    {
        for (size_t i = 0; i < indices.size(); i += 3) {
            Primitives::Triangle triangle;
            triangle.v0 = temp_vertices[indices[i]];
            triangle.v1 = temp_vertices[indices[i + 1]];
            triangle.v2 = temp_vertices[indices[i + 2]];

            // calculate the normal
            this->CalculateNormal(triangle);
    
            // execute backface culling
            if (enable_backface_culling)
            {
                if (this->IsBackface(triangle))
                {
                    continue;
                }
            }
    
            // execute frustum clipping
            if (enable_frustum_clipping)
            {
                if (
                    !this->IsInsideViewFrustum(triangle.v0) &&
                    !this->IsInsideViewFrustum(triangle.v1) &&
                    !this->IsInsideViewFrustum(triangle.v2)
                )
                {
                    continue;
                }
            }

            triangles.push_back(triangle);
        }

        // Transform to the screen space
        for (auto& triangle : triangles)
        {
            // NDC
            this->NDC(triangle.v0);
            this->NDC(triangle.v1);
            this->NDC(triangle.v2);
    
            // Viewport transformation
            this->ViewportTransformation(triangle.v0);
            this->ViewportTransformation(triangle.v1);
            this->ViewportTransformation(triangle.v2);
        }
    }

    // Prepare the all the vertex data for triangles
    else if (rendering_mode == RenderingMode::Triangles)
    {
        for (size_t i = 0; i < indices.size(); i += 3) {
            Primitives::Triangle triangle;
            triangle.v0 = temp_vertices[indices[i]];
            triangle.v1 = temp_vertices[indices[i + 1]];
            triangle.v2 = temp_vertices[indices[i + 2]];
    
            // calculate the normal
            this->CalculateNormal(triangle);

            // execute backface culling
            if (enable_backface_culling)
            {
                if (this->IsBackface(triangle))
                {
                    continue;
                }
            }
    
            // execute frustum clipping
            if (enable_frustum_clipping)
            {
                if (
                    !this->IsInsideViewFrustum(triangle.v0) &&
                    !this->IsInsideViewFrustum(triangle.v1) &&
                    !this->IsInsideViewFrustum(triangle.v2)
                )
                {
                    continue;
                }
            }

            triangles.push_back(triangle);
        }

        for (auto& triangle : triangles)
        {
            // Normalize the normal of all the vertices
            glm::normalize(triangle.v0.normal);
            glm::normalize(triangle.v1.normal);
            glm::normalize(triangle.v2.normal);

            // Shading
            if (shading_mode == ShadingMode::Flat)
            {
                this->FlatShading(triangle);
            }

            if (shading_mode == ShadingMode::Gourand)
            {
                this->GourandShading(triangle);
            }
    
            // NDC
            this->NDC(triangle.v0);
            this->NDC(triangle.v1);
            this->NDC(triangle.v2);
    
            // Viewport transformation
            this->ViewportTransformation(triangle.v0);
            this->ViewportTransformation(triangle.v1);
            this->ViewportTransformation(triangle.v2);
        }
    }

    return triangles;
}

bool VertexProcessing::IsBackface(const Primitives::Triangle& triangle) const
{
    // determine if the normal is back to the camera
    Vector3 viewDir = -glm::normalize(triangle.v0.pos);

    return glm::dot(triangle.normal, viewDir) < 0;
}

bool VertexProcessing::IsInsideViewFrustum(const Primitives::Vertex& vertex) const 
{
    float x = std::abs(vertex.pos.x);
    float y = std::abs(vertex.pos.y);
    float z = std::abs(vertex.pos.z);
    float w = std::abs(vertex.pos.w);

    return (x < w) && (y < w) && (z < w);
}

void VertexProcessing::NDC(Primitives::Vertex& vertex) const 
{
    float reciprocalW = 1.0f / vertex.pos.w;
    vertex.pos.x *= reciprocalW;
    vertex.pos.y *= reciprocalW;
    vertex.pos.z *= reciprocalW;
    vertex.pos.w = 1.0f;
}

void VertexProcessing::ViewportTransformation(Primitives::Vertex& vertex) const
{
    int screen_width = this->frame_buffer->GetWidth();
    int screen_height = this->frame_buffer->GetHeight();

    vertex.pos.x = (1.0f - vertex.pos.x) * 0.5f * screen_width;
    vertex.pos.y = (1.0f - vertex.pos.y) * 0.5f * screen_height;
    vertex.pos.z = vertex.pos.z;   // (depth_near = 1, depth_far = -1)
}

void VertexProcessing::CalculateNormal(Primitives::Triangle& triangle) const
{
    // calculate the normal
    Vector3 edge1 = triangle.v1.pos - triangle.v0.pos;
    Vector3 edge2 = triangle.v2.pos - triangle.v0.pos;
    triangle.normal = glm::normalize(glm::cross(edge1, edge2));

    triangle.v0.normal += triangle.normal;
    triangle.v1.normal += triangle.normal;
    triangle.v2.normal += triangle.normal;
}

void VertexProcessing::FlatShading(Primitives::Triangle& triangle) const
{
    // ambient
    Color ambient = this->light_ptr->ambient_intensity * this->material_ptr->diffuse_color;

    // diffuse
    float diff = std::max(0.0f, glm::dot(triangle.normal, this->light_ptr->dir));
    Color diffuse = this->light_ptr->diffuse_intensity * (material_ptr->diffuse_color * diff);

    // highlight
    Vector3 halfway_dir = glm::normalize(this->light_ptr->dir + this->camera_ptr->look_at);
    float spec = std::pow(std::max(0.0f, glm::dot(triangle.normal, halfway_dir)), material_ptr->shininess);
    Color specular = this->light_ptr->specular_intensity * (this->material_ptr->specular_color * spec);

    Color final_color = ambient + diffuse + specular;

    triangle.v0.color = final_color;
    triangle.v1.color = final_color;
    triangle.v2.color = final_color;
}

void VertexProcessing::GourandShading(Primitives::Triangle& triangle) const
{
    // ambient
    Color ambient = this->light_ptr->ambient_intensity * this->material_ptr->diffuse_color;

    // diffuse
    float diff = std::max(0.0f, glm::dot(triangle.normal, this->light_ptr->dir));
    Color diffuse = this->light_ptr->diffuse_intensity * (material_ptr->diffuse_color * diff);

    // highlight
    Vector3 halfway_dir = glm::normalize(this->light_ptr->dir + this->camera_ptr->look_at);
    float spec = std::pow(std::max(0.0f, glm::dot(triangle.normal, halfway_dir)), material_ptr->shininess);
    Color specular = this->light_ptr->specular_intensity * (this->material_ptr->specular_color * spec);

    Color final_color = ambient + diffuse + specular;
}