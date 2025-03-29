#include <core/pipeline/vertex_processing.h>

#include <iostream>

#include <glm/ext/matrix_transform.hpp> 

using namespace Pipeline;

VertexProcessing::VertexProcessing()
    : model_matrix{glm::identity<glm::mat4>()}
    , view_matrix{glm::identity<glm::mat4>()}
    , projection_matrix{glm::identity<glm::mat4>()}
    , frame_buffer{nullptr}
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

void VertexProcessing::NDC(Primitives::Vertex& vertex) const 
{
    float reciprocalW = 1.0f / vertex.pos.w;
    vertex.pos.x *= reciprocalW;
    vertex.pos.y *= reciprocalW;
    vertex.pos.z *= reciprocalW;
    vertex.pos.w = 1.0f;

    // std::cout << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << ", " << vertex.pos.w  << std::endl;
}

void VertexProcessing::ViewportTransformation(Primitives::Vertex& vertex) const
{
    int screen_width = this->frame_buffer->GetWidth();
    int screen_height = this->frame_buffer->GetHeight();

    vertex.pos.x = (1.0f - vertex.pos.x) * 0.5f * screen_width;
    vertex.pos.y = (1.0f - vertex.pos.y) * 0.5f * screen_height;
    vertex.pos.z = vertex.pos.z;   // (depth_near = 1, depth_far = -1)
}

std::vector<Primitives::Vertex> VertexProcessing::TransformVertices(
    const std::vector<Primitives::Vertex>& vertices) const 
{
    std::vector<Primitives::Vertex> result = vertices;

    const auto mvp = projection_matrix * (view_matrix * model_matrix);

    for (auto& vertex : result)
    {
        // 1. Apply MVP Matrix
        vertex.pos = mvp * vertex.pos;

        // 2. NDC
        this->NDC(vertex);

        // 3. Viewport transformation
        this->ViewportTransformation(vertex);
    }

    return result;
}