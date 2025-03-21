#include <core/pipeline/vertex_processing.h>

using namespace Core::Pipeline;

VertexProcessing::VertexProcessing()
    : model_matrix{Core::Math::Matrix4x4::GetIdentity()}
    , view_matrix{Core::Math::Matrix4x4::GetIdentity()}
    , projection_matrix{Core::Math::Matrix4x4::GetIdentity()}
    , frame_buffer{nullptr}
{

}

VertexProcessing::~VertexProcessing() = default;

void VertexProcessing::SetModelMatrix(const Core::Math::Matrix4x4& mat)
{
    this->model_matrix = mat;
}

void VertexProcessing::SetViewMatrix(const Core::Math::Matrix4x4& mat)
{
    this->view_matrix = mat;
}

void VertexProcessing::SetProjectionMatrix(const Core::Math::Matrix4x4& mat)
{
    this->projection_matrix = mat;
}

void VertexProcessing::SetFrameBuffer(std::shared_ptr<Core::Buffer::FrameBuffer> buffer)
{
    this->frame_buffer = buffer;
}

void VertexProcessing::NDC(Core::Primitives::Vertex& vertex) const 
{
    float reciprocalW = 1.0f / vertex.pos.w;
    vertex.pos.x *= reciprocalW;
    vertex.pos.y *= reciprocalW;
    vertex.pos.z *= reciprocalW;
    vertex.pos.w = 1.0f;
}

void VertexProcessing::ViewportTransformation(Core::Primitives::Vertex& vertex) const
{
    int screen_width = this->frame_buffer->GetWidth();
    int screen_height = this->frame_buffer->GetHeight();

    vertex.pos.x = (vertex.pos.x + 1.0f) * 0.5f * screen_width;
    vertex.pos.y = -(vertex.pos.y + 1.0f) * 0.5f * screen_height;
    vertex.pos.z = vertex.pos.z;   // (max_depth = 1, min_depth = 0)
}

std::vector<Core::Primitives::Vertex> VertexProcessing::TransformVertices(
    const std::vector<Core::Primitives::Vertex>& vertices) const 
{
    std::vector<Core::Primitives::Vertex> result = vertices;

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