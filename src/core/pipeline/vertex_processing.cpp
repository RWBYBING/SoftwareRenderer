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

std::vector<Core::Primitives::Vertex> VertexProcessing::TransformVertices(const std::vector<Core::Primitives::Vertex>& vertices) const
{
    std::vector<Core::Primitives::Vertex> result = vertices;
    for (long unsigned int i = 0; i < vertices.size(); ++i)
    {
        // Apply MVP transformation
        result.at(i).pos = this->projection_matrix * (this->view_matrix * (this->model_matrix * vertices.at(i).pos));
    }

    return result;
}