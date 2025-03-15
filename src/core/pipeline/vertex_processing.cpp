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

Core::Primitives::Vertex VertexProcessing::TransformVertex(const Core::Primitives::Vertex& vert)
{
    Core::Primitives::Vertex result = vert;

    // Apply MVP transformation
    result.pos = this->projection_matrix * (this->view_matrix * (this->model_matrix * result.pos));
}