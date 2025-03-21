#include <core/pipeline/vertex_processing.h>

using namespace Core::Pipeline;

VertexProcessing::VertexProcessing()
    : model_matrix{Core::Math::Matrix4x4::GetIdentity()}
    , view_matrix{Core::Math::Matrix4x4::GetIdentity()}
    , projection_matrix{Core::Math::Matrix4x4::GetIdentity()}
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

std::vector<Core::Primitives::Vertex> VertexProcessing::TransformVertices(
    const std::vector<Core::Primitives::Vertex>& vertices) const 
{
    const auto mvp = projection_matrix * (view_matrix * model_matrix);

    std::vector<Core::Primitives::Vertex> result = vertices;

    for (size_t i = 0; i < vertices.size(); ++i) {
        result[i].pos = mvp * vertices[i].pos;
    }
    result[0].pos.PrintVec();vertices[0].pos.PrintVec();

    return result;
}