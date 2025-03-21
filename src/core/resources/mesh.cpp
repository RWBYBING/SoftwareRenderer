#include <core/resources/mesh.h>

#include <cassert>

using namespace Core::Resources;

Mesh::Mesh()
    : vertices{}
    , indices{}
    , material{}
    , translation{0.0f, 0.0f, 0.0f}
    , rotation{0.0f, 0.0f, 0.0f}
    , scale{1.0f, 1.0f, 1.0f}
{
    
}

Mesh::~Mesh() = default;

void Mesh::AddVertex(const Core::Primitives::Vertex vert)
{
    this->vertices.push_back(vert);
}

void Mesh::AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2)
{
    assert(i0 < this->vertices.size() && i1 < this->vertices.size() && i2 < this->vertices.size());

    this->indices.push_back(i0);
    this->indices.push_back(i1);
    this->indices.push_back(i2);
}

Core::Math::Matrix4x4 Mesh::GetModelMatrix() const
{
    // Set model transformation matrix
    auto translation_matrix = Core::Math::Matrix4x4::Translation(this->translation);
    auto scale_matrix = Core::Math::Matrix4x4::Scale(this->scale);
    auto rotation_matrix = (
        Core::Math::Matrix4x4::Rotation(this->rotation.x, Core::Math::_3D_Cartesian_Coord::X) *
        Core::Math::Matrix4x4::Rotation(this->rotation.y, Core::Math::_3D_Cartesian_Coord::Y) *
        Core::Math::Matrix4x4::Rotation(this->rotation.z, Core::Math::_3D_Cartesian_Coord::Z)
    );

    return scale_matrix * (rotation_matrix * translation_matrix);
}